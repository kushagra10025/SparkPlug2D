#pragma once

#include <glm/glm.hpp>

namespace SP2D::Core::ECS
{
	struct TransformComponent
	{
		glm::vec2 position{ glm::vec2{0.f} };
		glm::vec2 scale{ glm::vec2{1.f} };
		float rotation{ 0.f };
	};
}
