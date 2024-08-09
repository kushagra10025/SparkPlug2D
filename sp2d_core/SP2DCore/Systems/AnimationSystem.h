#pragma once

#include "../ECS/Registry.h"

namespace SP2D::Core::Systems
{
	class AnimationSystem
	{
	private:
		SP2D::Core::ECS::Registry& m_Registry;
	public:
		AnimationSystem(SP2D::Core::ECS::Registry& registry);
		~AnimationSystem() = default;

		void Update();

	};
}
