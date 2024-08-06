#pragma once

#include "../ECS/Registry.h"
#include <SP2DRendering/Core/BatchRenderer.h>

namespace SP2D::Core::Systems
{
	class RenderSystem
	{
	private:
		ECS::Registry& m_Registry;
		std::unique_ptr<SP2D::Rendering::BatchRenderer> m_pBatchRenderer;

	public:
		RenderSystem(ECS::Registry& registry);
		~RenderSystem() = default;

		void Update();
	};
}
