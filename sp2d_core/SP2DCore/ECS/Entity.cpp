#include "Entity.h"
#include "Components/IdentificationComponent.h"
#include "MetaUtilities.h"

SP2D::Core::ECS::Entity::Entity(Registry& registry)
	: Entity(registry, "GameObject", "")
{

}

SP2D::Core::ECS::Entity::Entity(Registry& registry, const std::string& name /*= ""*/, const std::string& group /*= ""*/)
	:m_Registry{ registry }, m_Entity{ registry.CreateEntity() }, m_sName{ name }, m_sGroup{ group }
{
	AddComponent<IdentificationComponent>(IdentificationComponent{
			.name = name,
			.group = group,
			.entity_id = static_cast<int32_t>(m_Entity)
		});
}

SP2D::Core::ECS::Entity::Entity(Registry& registry, const entt::entity& entity)
	:m_Registry{ registry }, m_Entity{ entity }, m_sName{ "" }, m_sGroup{ "" }
{
	if (HasComponent<IdentificationComponent>())
	{
		auto id = GetComponent<IdentificationComponent>();
		m_sName = id.name;
		m_sGroup = id.group;
	}
}

void SP2D::Core::ECS::Entity::CreateLuaEntityBind(sol::state& lua, Registry& registry)
{
	using namespace entt::literals;
	lua.new_usertype<Entity>(
		"Entity",
		sol::call_constructor,
		sol::factories(
			[&](const std::string& name, const std::string& group) {
				return Entity{ registry, name, group };
			}
		),
		"add_component", [](Entity& entity, const sol::table& comp, sol::this_state s) -> sol::object {
			if (!comp.valid())
				return sol::lua_nil_t{};

			const auto component = SP2D::Core::ECS::Utils::InvokeMetaFunction(
				SP2D::Core::ECS::Utils::GetIdType(comp),
				"add_component"_hs,
				entity, comp, s
			);

			return component ? component.cast<sol::reference>() : sol::lua_nil_t{};
		},
		"has_component", [](Entity& entity, const sol::table& comp) -> bool {
			if (!comp.valid())
				return false;

			const auto component = SP2D::Core::ECS::Utils::InvokeMetaFunction(
				SP2D::Core::ECS::Utils::GetIdType(comp),
				"has_component"_hs,
				entity
			);

			return component ? component.cast<bool>() : false;
		},
		"get_component", [](Entity& entity, const sol::table& comp, sol::this_state s) -> sol::reference {
			if (!comp.valid())
				return sol::lua_nil_t{};

			const auto component = SP2D::Core::ECS::Utils::InvokeMetaFunction(
				SP2D::Core::ECS::Utils::GetIdType(comp),
				"get_component"_hs,
				entity, s
			);

			return component ? component.cast<sol::reference>() : sol::lua_nil_t{};
		},
		"remove_component", [](Entity& entity, const sol::table& comp) -> sol::reference {
			if (!comp.valid())
				return sol::lua_nil_t{};

			const auto component = SP2D::Core::ECS::Utils::InvokeMetaFunction(
				SP2D::Core::ECS::Utils::GetIdType(comp),
				"remove_component"_hs,
				entity
			);

			return component ? component.cast<sol::reference>() : sol::lua_nil_t{};
		},
		"name", &Entity::GetName,
		"group", &Entity::GetGroup,
		"kill", &Entity::Kill,
		"id", [](Entity& entity) { return static_cast<int32_t>(entity.GetEntity()); }
	);
}
