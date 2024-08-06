#pragma once

#include <sol/sol.hpp>

namespace SP2D::Core::ECS
{
	struct ScriptComponent
	{
		sol::protected_function update{ sol::lua_nil }, render{ sol::lua_nil };
	};
}