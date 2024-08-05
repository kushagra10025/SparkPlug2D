#include "Window.h"
#include <iostream>
#include <SP2DLogging/Log.h>

SP2D::Windowing::Window::Window(const std::string title, int width, int height, int xPos, int yPos, bool v_sync /*= true*/, Uint32 flags /*= (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE)*/)
	: m_pWindow{ nullptr }, m_GLContext{}, m_sTitle{title},
	m_Width{width}, m_Height{height}, m_XPos{xPos}, m_YPos{yPos}, m_WindowFlags{flags}
{
	CreateNewWindow(flags);

	// Enable v-sync
	if (v_sync)
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
			SP2D_CORE_ERROR("Failed to Enabled VSYNC!");
	}
}

SP2D::Windowing::Window::~Window()
{

}

void SP2D::Windowing::Window::CreateNewWindow(Uint32 flags)
{
	m_pWindow = WindowPtr(SDL_CreateWindow(
		m_sTitle.c_str(),
		m_XPos, m_YPos,
		m_Width, m_Height, flags
	));

	// Check if Window Created Correctly
	if (!m_pWindow)
	{
		std::string error = SDL_GetError();
		SP2D_CORE_ERROR("Failed to Create the Window\n{0}",error);
	}
}

void SP2D::Windowing::Window::SetWindowName(const std::string& name)
{
	m_sTitle = name;
	SDL_SetWindowTitle(m_pWindow.get(), name.c_str());
}

