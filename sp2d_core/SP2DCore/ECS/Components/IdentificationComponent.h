#pragma once

#include <string>

namespace SP2D::Core::ECS
{
	struct IdentificationComponent
	{
		std::string name{ "GameObject" };
		std::string group{ "" };
		std::int32_t entity_id{ -1 };
	};
}

