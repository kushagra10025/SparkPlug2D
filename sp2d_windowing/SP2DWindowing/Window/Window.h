#pragma once

#include <SP2DUtilities/SDL_Wrappers.h>
#include <string>

namespace SP2D::Windowing
{
	class Window
	{
	private:
		WindowPtr m_pWindow;
		SDL_GLContext m_GLContext;
		std::string m_sTitle;
		int m_Width, m_Height, m_XPos, m_YPos;
		Uint32 m_WindowFlags;

	private:
		void CreateNewWindow(Uint32 flags);

	public:
		Window() : Window("default_window", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true, NULL)
		{

		}

		Window(const std::string title, 
			int width, int height, 
			int xPos, int yPos,
			bool v_sync = true,
			Uint32 flags = (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE));
		
		~Window();

		
		inline SDL_GLContext& GetGLContext() { return m_GLContext; }
		inline WindowPtr& GetWindow() { return m_pWindow; }
		inline const std::string& GetWindowName() const { return m_sTitle; }
		inline const int GetXPos() const { return m_XPos; }
		inline const int GetYPos() const { return m_YPos; }
		inline const int GetWidth() const { return m_Width; }
		inline const int GetHeight() const { return m_Height; }

		inline void SetGLContext(SDL_GLContext glContext) { m_GLContext = glContext; }
		inline const int SetXPos(int xPos) { m_XPos = xPos; }
		inline const int SetYPos(int yPos) { m_YPos = yPos; }

		void SetWindowName(const std::string& name);
	};
}
