#pragma once

#include <entt/entt.hpp>
#include <sol/sol.hpp>

namespace SP2D::Core::ECS
{
	class Registry
	{
	private:
		std::unique_ptr<entt::registry> m_pRegistry;

	public:
		Registry();
		~Registry() = default;

		inline entt::registry& GetRegistry() { return *m_pRegistry; }
		inline entt::entity CreateEntity() { return m_pRegistry->create(); }

		template <typename TContext>
		TContext AddToContext(TContext context);

		template <typename TContext>
		TContext& GetContext();

		static void CreateLuaRegistryBind(sol::state& lua, Registry& registry);

		template <typename TComponent>
		static void RegisterMetaComponent();
	};

	template <typename TComponent>
	entt::runtime_view& add_component_to_view(Registry* registry, entt::runtime_view& view);

	template <typename TComponent>
	entt::runtime_view& exclude_component_from_view(Registry* registry, entt::runtime_view& view);
}

#include "Registry.inl"