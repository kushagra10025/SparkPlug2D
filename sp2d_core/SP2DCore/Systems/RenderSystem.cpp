#include "RenderSystem.h"

#include "../Resources/AssetManager.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include <SP2DRendering/Core/Camera2D.h>
#include <SP2DRendering/Essentials/Shader.h>
#include <SP2DLogging/Log.h>

SP2D::Core::Systems::RenderSystem::RenderSystem(ECS::Registry& registry)
	: m_Registry{ registry }, m_pBatchRenderer{ nullptr }
{
	m_pBatchRenderer = std::make_unique<SP2D::Rendering::BatchRenderer>();
}

void SP2D::Core::Systems::RenderSystem::Update()
{
	auto& camera = m_Registry.GetContext<std::shared_ptr<SP2D::Rendering::Camera2D>>();
	if (!camera)
	{
		SP2D_ERROR("Failed to get the Camera2D from Registry Context!");
		return;
	}
	auto& assetManager = m_Registry.GetContext<std::shared_ptr<SP2D::Core::Resources::AssetManager>>();
	if (!assetManager)
	{
		SP2D_ERROR("Failed to get the AssetManager from Registry Context!");
		return;
	}

	auto& spriteShader = assetManager->GetShader("basicShader");
	auto cam_mat = camera->GetCameraMatrix();

	if (spriteShader.ShaderProgramID() == 0)
	{
		SP2D_CORE_ERROR("Sprite Shader Program has not been set correctly!");
		return;
	}
	
	// Enable Shader
	spriteShader.Enable();
	spriteShader.SetUniformMat4("uProjection", cam_mat);

	m_pBatchRenderer->Begin();

	auto view = m_Registry.GetRegistry().view<ECS::SpriteComponent, ECS::TransformComponent>();

	for (const auto& entity : view)
	{
		const auto& transform = view.get<ECS::TransformComponent>(entity);
		const auto& sprite = view.get<ECS::SpriteComponent>(entity);

		if(sprite.texture_name.empty())
			continue;

		const auto& texture = assetManager->GetTexture(sprite.texture_name);
		if (texture.GetID() == 0)
		{
			SP2D_CORE_ERROR("Texture [{0}] not created correctly!", sprite.texture_name);
			return;
		}

		glm::vec4 spriteRect{ transform.position.x, transform.position.y, sprite.width, sprite.height };
		glm::vec4 uvRect{ sprite.uvs.u, sprite.uvs.v, sprite.uvs.uv_width, sprite.uvs.uv_height };

		glm::mat4 model{ 1.f };

		if (transform.rotation > 0.f || transform.rotation < 0.f ||
			transform.scale.x > 1.f || transform.scale.x < 1.f ||
			transform.scale.y > 1.f || transform.scale.y < 1.f)
		{
			model = glm::translate(model, glm::vec3{ transform.position, 0.f });
			model = glm::translate(model, glm::vec3{ (sprite.width * transform.scale.x) * 0.5f, (sprite.height * transform.scale.y) * 0.5f, 0.f });
			model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3{ 0.f, 0.f, 1.f });
			model = glm::translate(model, glm::vec3{ (sprite.width * transform.scale.x) * -0.5f, (sprite.height * transform.scale.y) * -0.5f, 0.f });
			model = glm::scale(model, glm::vec3{ transform.scale, 1.f });
			model = glm::translate(model, glm::vec3{ -transform.position, 0.f });
		}

		m_pBatchRenderer->AddSprite(spriteRect, uvRect, texture.GetID(), sprite.layer, model, sprite.color);
	}

	m_pBatchRenderer->End();
	m_pBatchRenderer->Render();

	spriteShader.Disable();
}

