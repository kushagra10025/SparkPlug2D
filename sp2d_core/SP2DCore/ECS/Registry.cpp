#include "Registry.h"


SP2D::Core::ECS::Registry::Registry()
	:m_pRegistry{nullptr}
{
	m_pRegistry = std::make_unique<entt::registry>();
}

