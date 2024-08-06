#pragma once

#include "../ECS/Registry.h"
#include <sol/sol.hpp>

namespace SP2D::Core::Systems
{
	class ScriptingSystem
	{
	private:
		ECS::Registry& m_Registry;
		bool m_bMainLoaded;

	public:
		ScriptingSystem(ECS::Registry& registry);
		~ScriptingSystem() = default;

		bool LoadMainScript(sol::state& lua);
		void Update();
		void Render();
	};
}
