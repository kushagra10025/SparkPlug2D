#pragma once

#include <glad/glad.h>
#include <SP2DWindowing/Window/Window.h>
#include <SP2DCore/ECS/Registry.h>

namespace SP2D::Editor
{
	class Application
	{
	private:
		std::unique_ptr<SP2D::Windowing::Window> m_pWindow;
		std::unique_ptr<SP2D::Core::ECS::Registry> m_pRegistry;

		SDL_Event m_Event;
		bool m_bIsRunning;

	private:
		bool Initialize();
		bool LoadShaders();

		void ProcessEvents();
		void Update();
		void Render();
		
		void Cleanup();

		Application();
		~Application() = default;
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

	public:
		static Application& GetInstance();

		void Run();
	};
}