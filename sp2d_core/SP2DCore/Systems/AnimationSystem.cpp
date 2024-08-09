#include "AnimationSystem.h"
#include "../ECS/Components/AnimationComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include <SDL.h>


SP2D::Core::Systems::AnimationSystem::AnimationSystem(SP2D::Core::ECS::Registry& registry)
	: m_Registry(registry)
{

}

void SP2D::Core::Systems::AnimationSystem::Update()
{
	auto view = m_Registry.GetRegistry().view<SP2D::Core::ECS::AnimationComponent, SP2D::Core::ECS::SpriteComponent, SP2D::Core::ECS::TransformComponent>();

	for (auto entity : view)
	{
		const auto& transform = view.get<SP2D::Core::ECS::TransformComponent>(entity);
		auto& sprite = view.get<SP2D::Core::ECS::SpriteComponent>(entity);
		auto& animation = view.get<SP2D::Core::ECS::AnimationComponent>(entity);

		animation.currentFrame = (SDL_GetTicks() * animation.frameRate / 1000) % animation.numFrames;

		if (animation.bVertical)
		{
			sprite.uvs.v = animation.currentFrame * sprite.uvs.uv_width;
			sprite.uvs.u = animation.frameOffset * sprite.uvs.uv_width;
		}
		else
		{
			sprite.uvs.u = (animation.currentFrame * sprite.uvs.uv_width) + (animation.frameOffset * sprite.uvs.uv_width);
		}
	}
}
