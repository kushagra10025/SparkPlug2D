#include "Mouse.h"
#include <SDL.h>
#include <SP2DLogging/Log.h>

void SP2D::Windowing::Inputs::Mouse::Update()
{
	for (auto& [btn, button] : m_mapButtons)
	{
		button.Reset();
	}

	m_WheelX = 0;
	m_WheelY = 0;
	m_bMouseMoving = false;
}

void SP2D::Windowing::Inputs::Mouse::OnButtonPressed(int button)
{
	if (button == SP2D_MOUSE_UNKNOWN)
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] is Unknown!", button);
		return;
	}

	auto buttonItr = m_mapButtons.find(button);

	if (buttonItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] does not exist!", button);
		return;
	}
	
	buttonItr->second.Update(true);
}

void SP2D::Windowing::Inputs::Mouse::OnButtonReleased(int button)
{
	if (button == SP2D_MOUSE_UNKNOWN)
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] is Unknown!", button);
		return;
	}

	auto buttonItr = m_mapButtons.find(button);

	if (buttonItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] does not exist!", button);
		return;
	}

	buttonItr->second.Update(false);
}

const bool SP2D::Windowing::Inputs::Mouse::IsButtonPressed(int button) const
{
	if (button == SP2D_MOUSE_UNKNOWN)
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] is Unknown!", button);
		return false;
	}

	auto buttonItr = m_mapButtons.find(button);

	if (buttonItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] does not exist!", button);
		return false;
	}

	return buttonItr->second.bIsPressed;
}

const bool SP2D::Windowing::Inputs::Mouse::IsButtonJustPressed(int button) const
{
	if (button == SP2D_MOUSE_UNKNOWN)
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] is Unknown!", button);
		return false;
	}

	auto buttonItr = m_mapButtons.find(button);

	if (buttonItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] does not exist!", button);
		return false;
	}

	return buttonItr->second.bJustPressed;
}

const bool SP2D::Windowing::Inputs::Mouse::IsButtonJustReleased(int button) const
{
	if (button == SP2D_MOUSE_UNKNOWN)
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] is Unknown!", button);
		return false;
	}

	auto buttonItr = m_mapButtons.find(button);

	if (buttonItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Mouse Button [{0}] does not exist!", button);
		return false;
	}

	return buttonItr->second.bJustReleased;
}

const std::tuple<int, int> SP2D::Windowing::Inputs::Mouse::GetMouseScreenPosition()
{
	SDL_GetMouseState(&m_X, &m_Y);
	return std::make_tuple(m_X, m_Y);
}

