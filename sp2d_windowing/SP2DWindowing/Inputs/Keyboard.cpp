#include "Keyboard.h"
#include <SP2DLogging/Log.h>

SP2D::Windowing::Inputs::Keyboard::Keyboard()
	:m_mapButtons{
		{SP2D_KEY_BACKSPACE, Button{}}, {SP2D_KEY_TAB, Button{}}, {SP2D_KEY_CLEAR, Button{}},
		{SP2D_KEY_RETURN, Button{}}, {SP2D_KEY_PAUSE, Button{}}, {SP2D_KEY_ESCAPE, Button{}}, {SP2D_KEY_SPACE, Button{}},
		{SP2D_KEY_EXCLAIM, Button{}}, {SP2D_KEY_QUOTEDBL, Button{}}, {SP2D_KEY_HASH, Button{}}, {SP2D_KEY_DOLLAR, Button{}},
		{SP2D_KEY_AMPERSAND, Button{}}, {SP2D_KEY_QUOTE, Button{}}, {SP2D_KEY_LEFTPAREN, Button{}}, {SP2D_KEY_RIGHTPAREN, Button{}},
		{SP2D_KEY_ASTERISK, Button{}}, {SP2D_KEY_PLUS, Button{}}, {SP2D_KEY_COMMA, Button{}}, {SP2D_KEY_PERIOD, Button{}},
		{SP2D_KEY_SLASH, Button{}}, {SP2D_KEY_0, Button{}}, {SP2D_KEY_2, Button{}}, {SP2D_KEY_3, Button{}},
		{SP2D_KEY_4, Button{}}, {SP2D_KEY_5, Button{}}, {SP2D_KEY_6, Button{}}, {SP2D_KEY_7, Button{}},
		{SP2D_KEY_8, Button{}}, {SP2D_KEY_9, Button{}}, {SP2D_KEY_COLON, Button{}}, {SP2D_KEY_SEMICOLON, Button{}},
		{SP2D_KEY_LESS, Button{}}, {SP2D_KEY_EQUALS, Button{}}, {SP2D_KEY_GREATER, Button{}}, {SP2D_KEY_QUESTION, Button{}},
		{SP2D_KEY_AT, Button{}}, {SP2D_KEY_LEFTBRACKET, Button{}}, {SP2D_KEY_BACKSLASH, Button{}}, {SP2D_KEY_RIGHTBRACKET, Button{}},
		{SP2D_KEY_CARET, Button{}}, {SP2D_KEY_UNDERSCORE, Button{}}, {SP2D_KEY_A, Button{}}, {SP2D_KEY_B, Button{}},
		{SP2D_KEY_C, Button{}}, {SP2D_KEY_D, Button{}}, {SP2D_KEY_E, Button{}}, {SP2D_KEY_F, Button{}},
		{SP2D_KEY_G, Button{}}, {SP2D_KEY_H, Button{}}, {SP2D_KEY_I, Button{}}, {SP2D_KEY_J, Button{}},
		{SP2D_KEY_K, Button{}}, {SP2D_KEY_L, Button{}}, {SP2D_KEY_M, Button{}}, {SP2D_KEY_N, Button{}},
		{SP2D_KEY_O, Button{}}, {SP2D_KEY_P, Button{}}, {SP2D_KEY_Q, Button{}}, {SP2D_KEY_R, Button{}},
		{SP2D_KEY_S, Button{}}, {SP2D_KEY_T, Button{}}, {SP2D_KEY_U, Button{}}, {SP2D_KEY_V, Button{}},
		{SP2D_KEY_W, Button{}}, {SP2D_KEY_X, Button{}}, {SP2D_KEY_Y, Button{}}, {SP2D_KEY_Z, Button{}},
		{SP2D_KEY_DELETE, Button{}}, {SP2D_KEY_CAPSLOCK, Button{}}, {SP2D_KEY_F1, Button{}}, {SP2D_KEY_F2, Button{}},
		{SP2D_KEY_F3, Button{}}, {SP2D_KEY_F4, Button{}}, {SP2D_KEY_F5, Button{}}, {SP2D_KEY_F6, Button{}},
		{SP2D_KEY_F7, Button{}}, {SP2D_KEY_F8, Button{}}, {SP2D_KEY_F9, Button{}}, {SP2D_KEY_F10, Button{}},
		{SP2D_KEY_F11, Button{}}, {SP2D_KEY_F12, Button{}}, {SP2D_KEY_SCROLLOCK, Button{}}, {SP2D_KEY_INSERT, Button{}},
		{SP2D_KEY_HOME, Button{}}, {SP2D_KEY_PAGEUP, Button{}}, {SP2D_KEY_PAGEDOWN, Button{}}, {SP2D_KEY_END, Button{}},
		{SP2D_KEY_RIGHT, Button{}}, {SP2D_KEY_LEFT, Button{}}, {SP2D_KEY_DOWN, Button{}}, {SP2D_KEY_UP, Button{}},
		{SP2D_KEY_NUMLOCK, Button{}}, {SP2D_KEY_KP_DIVIDE, Button{}}, {SP2D_KEY_KP_MULTIPLY, Button{}}, {SP2D_KEY_KP_MINUS, Button{}},
		{SP2D_KEY_KP_PLUS, Button{}}, {SP2D_KEY_KP_ENTER, Button{}}, {SP2D_KEY_KP1, Button{}}, {SP2D_KEY_KP2, Button{}},
		{SP2D_KEY_KP3, Button{}}, {SP2D_KEY_KP4, Button{}}, {SP2D_KEY_KP5, Button{}}, {SP2D_KEY_KP6, Button{}},
		{SP2D_KEY_KP7, Button{}}, {SP2D_KEY_KP8, Button{}}, {SP2D_KEY_KP9, Button{}}, {SP2D_KEY_KP0, Button{}},
		{SP2D_KEY_KP_PERIOD, Button{}}, {SP2D_KEY_LCTRL, Button{}}, {SP2D_KEY_LSHIFT, Button{}},
		{SP2D_KEY_LALT, Button{}}, {SP2D_KEY_RCTRL, Button{}}, {SP2D_KEY_RSHIFT, Button{}}, {SP2D_KEY_RALT, Button{}}
	}
{

}

void SP2D::Windowing::Inputs::Keyboard::Update()
{
	for (auto& [key, button] : m_mapButtons)
	{
		button.Reset();
	}
}

void SP2D::Windowing::Inputs::Keyboard::OnKeyPressed(int key)
{
	if (key == KEY_UNKNOWN)
	{
		SP2D_CORE_ERROR("Key [{0}] is Unknown!", key);
		return;
	}
	auto keyItr = m_mapButtons.find(key);
	if (keyItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Key [{0}] does not exist!", key);
		return;
	}

	keyItr->second.Update(true);
}

void SP2D::Windowing::Inputs::Keyboard::OnKeyReleased(int key)
{
	if (key == KEY_UNKNOWN)
	{
		SP2D_CORE_ERROR("Key [{0}] is Unknown!", key);
		return;
	}
	auto keyItr = m_mapButtons.find(key);
	if (keyItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Key [{0}] does not exist!", key);
		return;
	}

	keyItr->second.Update(false);
}

const bool SP2D::Windowing::Inputs::Keyboard::IsKeyPressed(int key) const
{
	if (key == KEY_UNKNOWN)
	{
		SP2D_CORE_ERROR("Key [{0}] is Unknown!", key);
		return false;
	}
	auto keyItr = m_mapButtons.find(key);
	if (keyItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Key [{0}] does not exist!", key);
		return false;
	}

	return keyItr->second.bIsPressed;
}

const bool SP2D::Windowing::Inputs::Keyboard::IsKeyJustPressed(int key) const
{
	if (key == KEY_UNKNOWN)
	{
		SP2D_CORE_ERROR("Key [{0}] is Unknown!", key);
		return false;
	}
	auto keyItr = m_mapButtons.find(key);
	if (keyItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Key [{0}] does not exist!", key);
		return false;
	}

	return keyItr->second.bJustPressed;
}

const bool SP2D::Windowing::Inputs::Keyboard::IsKeyJustReleased(int key) const
{
	if (key == KEY_UNKNOWN)
	{
		SP2D_CORE_ERROR("Key [{0}] is Unknown!", key);
		return false;
	}
	auto keyItr = m_mapButtons.find(key);
	if (keyItr == m_mapButtons.end())
	{
		SP2D_CORE_ERROR("Key [{0}] does not exist!", key);
		return false;
	}

	return keyItr->second.bJustReleased;
}
