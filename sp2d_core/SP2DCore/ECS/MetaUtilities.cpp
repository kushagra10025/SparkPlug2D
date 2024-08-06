#include "MetaUtilities.h"

entt::id_type SP2D::Core::ECS::Utils::GetIdType(const sol::table& comp)
{
	if (!comp.valid())
	{
		SP2D_CORE_ERROR("Failed to get type id -- Component not exposed to Lua");
		assert(comp.valid() && "Failed to get type id -- Component not exposed to Lua");
		return -1;
	}

	const auto func = comp["type_id"].get<sol::function>();
	assert(func.valid() &&
		"[type_id()] - function has not been exposed to lua!"
		"\nPlease ensure all components and types have a type_id function"
		"\nwhen creating the new usertype"
	);

	return func.valid() ? func().get<entt::id_type>() : -1;
}
