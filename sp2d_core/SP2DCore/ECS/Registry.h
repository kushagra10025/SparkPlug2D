#pragma once

#include <entt/entt.hpp>

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
	};

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

}