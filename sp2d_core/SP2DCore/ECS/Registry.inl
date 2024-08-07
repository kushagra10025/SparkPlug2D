#include "Registry.h"

template <typename TContext>
inline TContext SP2D::Core::ECS::Registry::AddToContext(TContext context)
{
	return m_pRegistry->ctx().emplace<TContext>(context);
}

template <typename TContext>
inline TContext& SP2D::Core::ECS::Registry::GetContext()
{
	return m_pRegistry->ctx().get<TContext>();
}

template <typename TComponent>
entt::runtime_view& SP2D::Core::ECS::add_component_to_view(Registry* registry, entt::runtime_view& view)
{
	return view.iterate(registry->GetRegistry().storage<TComponent>());
}

template <typename TComponent>
entt::runtime_view& SP2D::Core::ECS::exclude_component_from_view(Registry* registry, entt::runtime_view& view)
{
	return view.exclude(registry->GetRegistry().storage<TComponent>());
}

template <typename TComponent>
void SP2D::Core::ECS::Registry::RegisterMetaComponent()
{
	using namespace entt::literals;
	entt::meta<TComponent>()
		.type(entt::type_hash<TComponent>::value())
		.template func<&add_component_to_view<TComponent>>("add_component_to_view"_hs)
		.template func<&exclude_component_from_view<TComponent>>("exclude_component_from_view"_hs);
}
