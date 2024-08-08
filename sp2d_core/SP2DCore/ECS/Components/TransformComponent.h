#pragma once

#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <entt/entt.hpp>

namespace SP2D::Core::ECS
{
	struct TransformComponent
	{
		glm::vec2 position{ glm::vec2{0.f} };
		glm::vec2 scale{ glm::vec2{1.f} };
		float rotation{ 0.f };

		static void CreateLuaTransformBind(sol::state& lua)
		{
			lua.new_usertype<TransformComponent>(
				"Transform",
				"type_id", &entt::type_hash<TransformComponent>::value,
				sol::call_constructor,
				sol::factories(
					[](glm::vec2 position, glm::vec2 scale, float rotation) {
						return TransformComponent{
							.position = position,
							.scale = scale,
							.rotation = rotation
						};
					},
					[](float x, float y, float scale_x, float scale_y, float rotation) {
						return TransformComponent{
							.position = glm::vec2{x, y},
							.scale = glm::vec2{scale_x, scale_y},
							.rotation = rotation
						};
					}
				),
				"position", &TransformComponent::position,
				"scale", &TransformComponent::scale,
				"rotation", &TransformComponent::rotation
			);
		}
	};
}
