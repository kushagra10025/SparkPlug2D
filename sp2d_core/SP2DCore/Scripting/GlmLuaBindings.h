#pragma once

#include <sol/sol.hpp>

namespace SP2D::Core::Scripting
{
	struct GLMBindings
	{
		static void CreateLuaGLMBindings(sol::state& lua);
	};
}