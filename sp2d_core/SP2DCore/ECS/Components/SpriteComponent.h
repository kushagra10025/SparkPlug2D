#pragma once

#include "../Registry.h"
#include "../../Resources/AssetManager.h"
#include <sol/sol.hpp>
#include <SP2DRendering/Essentials/Vertex.h>
#include <SP2DLogging/Log.h>

namespace SP2D::Core::ECS
{
	struct UVs
	{
		float u{ 0.f }, v{ 0.f }, uv_width{ 0.f }, uv_height{ 0.f };
	};

	struct SpriteComponent
	{
		float width{ 0.f }, height{ 0.f };
		UVs uvs{ .u = 0.f, .v = 0.f, .uv_width = 0.f, .uv_height = 0.f };

		SP2D::Rendering::Color color{ .r = 255, .g = 255, .b = 255, .a = 255 };
		int start_x{ 0 }, start_y{ 0 }, layer{ 0 };

		std::string texture_name{ "" };

		void generate_uvs(int textureWidth, int textureHeight)
		{
			uvs.uv_width = width / textureWidth;
			uvs.uv_height = height / textureHeight;

			uvs.u = start_x * uvs.uv_width;
			uvs.v = start_y * uvs.uv_height;
		}

		static void CreateLuaSpriteBind(sol::state& lua, SP2D::Core::ECS::Registry& registry)
		{
			lua.new_usertype<SpriteComponent>(
				"Sprite",
				"type_id", &entt::type_hash<SpriteComponent>::value,
				sol::call_constructor,
				sol::factories(
					[](const std::string& textureName, float width, float height, int start_x, int start_y, int layer) {
						return SpriteComponent{
							.width = width,
							.height = height,
							.uvs = UVs{},
							.color = SP2D::Rendering::Color{ 255, 255, 255, 255 },
							.start_x = start_x,
							.start_y = start_y,
							.layer = layer,
							.texture_name = textureName
						};
					}
				),
				"texture_name", &SpriteComponent::texture_name,
				"width", &SpriteComponent::width,
				"height", &SpriteComponent::height,
				"start_x", &SpriteComponent::start_x,
				"start_y", &SpriteComponent::start_y,
				"layer", &SpriteComponent::layer,
				"generate_uvs", [&](SpriteComponent& sprite) {
					auto& assetManager = registry.GetContext<std::shared_ptr<SP2D::Core::Resources::AssetManager>>();
					auto& texture = assetManager->GetTexture(sprite.texture_name);

					if (texture.GetID() == 0)
					{
						SP2D_CORE_ERROR("Failed to Generate UVs for Texture [{0}]", sprite.texture_name);
						return;
					}

					sprite.generate_uvs(texture.GetWidth(), texture.GetHeight());
				}
			);
		}
	};
}
