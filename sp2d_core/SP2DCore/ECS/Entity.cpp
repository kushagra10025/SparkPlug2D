#include "Entity.h"
#include "Components/IdentificationComponent.h"

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
