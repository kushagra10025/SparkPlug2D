#include "InputManager.h"

SP2D::Core::Scripting::InputManager::InputManager()
	: m_pKeyboard{ std::make_unique<SP2D::Windowing::Inputs::Keyboard>() },
	m_pMouse{std::make_unique<SP2D::Windowing::Inputs::Mouse>()}
{

}

void SP2D::Core::Scripting::InputManager::RegisterLuaKeyNames(sol::state& lua)
{
	// Register Typewriter Keys
	lua.set("KEY_A", SP2D_KEY_A);
	lua.set("KEY_B", SP2D_KEY_B);
	lua.set("KEY_C", SP2D_KEY_C);
	lua.set("KEY_D", SP2D_KEY_D);
	lua.set("KEY_E", SP2D_KEY_E);
	lua.set("KEY_F", SP2D_KEY_F);
	lua.set("KEY_G", SP2D_KEY_G);
	lua.set("KEY_H", SP2D_KEY_H);
	lua.set("KEY_I", SP2D_KEY_I);
	lua.set("KEY_J", SP2D_KEY_J);
	lua.set("KEY_K", SP2D_KEY_K);
	lua.set("KEY_L", SP2D_KEY_L);
	lua.set("KEY_M", SP2D_KEY_M);
	lua.set("KEY_N", SP2D_KEY_N);
	lua.set("KEY_O", SP2D_KEY_O);
	lua.set("KEY_P", SP2D_KEY_P);
	lua.set("KEY_Q", SP2D_KEY_Q);
	lua.set("KEY_R", SP2D_KEY_R);
	lua.set("KEY_S", SP2D_KEY_S);
	lua.set("KEY_T", SP2D_KEY_T);
	lua.set("KEY_U", SP2D_KEY_U);
	lua.set("KEY_V", SP2D_KEY_V);
	lua.set("KEY_W", SP2D_KEY_W);
	lua.set("KEY_X", SP2D_KEY_X);
	lua.set("KEY_Y", SP2D_KEY_Y);
	lua.set("KEY_Z", SP2D_KEY_Z);

	lua.set("KEY_0", SP2D_KEY_0);
	lua.set("KEY_1", SP2D_KEY_1);
	lua.set("KEY_2", SP2D_KEY_2);
	lua.set("KEY_3", SP2D_KEY_3);
	lua.set("KEY_4", SP2D_KEY_4);
	lua.set("KEY_5", SP2D_KEY_5);
	lua.set("KEY_6", SP2D_KEY_6);
	lua.set("KEY_7", SP2D_KEY_7);
	lua.set("KEY_8", SP2D_KEY_8);
	lua.set("KEY_9", SP2D_KEY_9);

	lua.set("KEY_ENTER", SP2D_KEY_RETURN);
	lua.set("KEY_BACKSPACE", SP2D_KEY_BACKSPACE);
	lua.set("KEY_ESC", SP2D_KEY_ESCAPE);
	lua.set("KEY_SPACE", SP2D_KEY_SPACE);
	lua.set("KEY_LCTRL", SP2D_KEY_LCTRL);
	lua.set("KEY_RCTRL", SP2D_KEY_RCTRL);
	lua.set("KEY_LALT", SP2D_KEY_LALT);
	lua.set("KEY_RALT", SP2D_KEY_RALT);
	lua.set("KEY_LSHIFT", SP2D_KEY_LSHIFT);
	lua.set("KEY_RSHIFT", SP2D_KEY_RSHIFT);

	//  Register Function Keys
	lua.set("KEY_F1", SP2D_KEY_F1);
	lua.set("KEY_F2", SP2D_KEY_F2);
	lua.set("KEY_F3", SP2D_KEY_F3);
	lua.set("KEY_F4", SP2D_KEY_F4);
	lua.set("KEY_F5", SP2D_KEY_F5);
	lua.set("KEY_F6", SP2D_KEY_F6);
	lua.set("KEY_F7", SP2D_KEY_F7);
	lua.set("KEY_F8", SP2D_KEY_F8);
	lua.set("KEY_F9", SP2D_KEY_F9);
	lua.set("KEY_F10", SP2D_KEY_F10);
	lua.set("KEY_F11", SP2D_KEY_F11);
	lua.set("KEY_F12", SP2D_KEY_F12);

	// Register Cursor Control Keys
	lua.set("KEY_UP", SP2D_KEY_UP);
	lua.set("KEY_RIGHT", SP2D_KEY_RIGHT);
	lua.set("KEY_DOWN", SP2D_KEY_DOWN);
	lua.set("KEY_LEFT", SP2D_KEY_LEFT);

	// Register Numeric Keypad Keys
	lua.set("KP_KEY_0", SP2D_KEY_KP0);
	lua.set("KP_KEY_1", SP2D_KEY_KP1);
	lua.set("KP_KEY_2", SP2D_KEY_KP2);
	lua.set("KP_KEY_3", SP2D_KEY_KP3);
	lua.set("KP_KEY_4", SP2D_KEY_KP4);
	lua.set("KP_KEY_5", SP2D_KEY_KP5);
	lua.set("KP_KEY_6", SP2D_KEY_KP6);
	lua.set("KP_KEY_7", SP2D_KEY_KP7);
	lua.set("KP_KEY_8", SP2D_KEY_KP8);
	lua.set("KP_KEY_9", SP2D_KEY_KP9);
	lua.set("KP_KEY_ENTER", SP2D_KEY_KP_ENTER);
}

void SP2D::Core::Scripting::InputManager::RegisterLuaMouseButtonNames(sol::state& lua)
{
	// Register Mouse Buttons
	lua.set("LEFT_MOUSE_BTN", SP2D_MOUSE_LEFT);
	lua.set("RIGHT_MOUSE_BTN", SP2D_MOUSE_RIGHT);
	lua.set("MIDDLE_MOUSE_BTN", SP2D_MOUSE_MIDDLE);
}

SP2D::Core::Scripting::InputManager& SP2D::Core::Scripting::InputManager::GetInstance()
{
	static InputManager instance{};
	return instance;
}

void SP2D::Core::Scripting::InputManager::CreateLuaInputBindings(sol::state& lua)
{
	RegisterLuaKeyNames(lua);
	RegisterLuaMouseButtonNames(lua);

	auto& inputManager = GetInstance();
	auto& keyboard = inputManager.GetKeyboard();

	lua.new_usertype<SP2D::Windowing::Inputs::Keyboard>(
		"Keyboard",
		sol::no_constructor,
		"just_pressed", [&](int key) { return keyboard.IsKeyJustPressed(key); },
		"just_released", [&](int key) { return keyboard.IsKeyJustReleased(key); },
		"pressed", [&](int key) { return keyboard.IsKeyPressed(key); }
	);

	auto& mouse = inputManager.GetMouse();
	lua.new_usertype<SP2D::Windowing::Inputs::Mouse>(
		"Mouse",
		sol::no_constructor,
		"just_pressed", [&](int key) { return mouse.IsButtonJustPressed(key); },
		"just_released", [&](int key) { return mouse.IsButtonJustReleased(key); },
		"pressed", [&](int key) { return mouse.IsButtonPressed(key); },
		"moving", [&]() { return mouse.IsMouseMoving(); },
		"screen_position", [&]() { return mouse.GetMouseScreenPosition(); },
		"wheel_x", [&]() { return mouse.GetMouseWheelX(); },
		"wheel_y", [&]() { return mouse.GetMouseWheelY(); }
	);
}
