#pragma once
#include "Entity.h"

namespace SP2D::Core::ECS
{
	template <typename TComponent, typename ...Args>
	TComponent& Entity::AddComponent(Args&& ...args)
	{
		auto& registry = m_Registry.GetRegistry();
		return registry.emplace<TComponent>(m_Entity, std::forward<Args>(args) ...);
	}

	template <typename TComponent, typename ...Args>
	TComponent& Entity::ReplaceComponent(Args&& ...args)
	{
		auto& registry = m_Registry.GetRegistry();
		if(registry.all_of<TComponent>(m_Entity))
			return registry.replace<TComponent>(m_Entity, std::forward<Args>(args) ...);
		else
			return registry.emplace<TComponent>(m_Entity, std::forward<Args>(args) ...);
	}

	template <typename TComponent>
	TComponent& Entity::GetComponent()
	{
		auto& registry = m_Registry.GetRegistry();
		return registry.get<TComponent>(m_Entity);
	}

	template <typename TComponent>
	bool Entity::HasComponent()
	{
		auto& registry = m_Registry.GetRegistry();
		return registry.all_of<TComponent>(m_Entity);
	}

	template <typename TComponent>
	void Entity::RemoveComponent()
	{
		// TODO Check if has entity before removing.
		auto& registry = m_Registry.GetRegistry();
		registry.remove<TComponent>(m_Entity);	
	}
}