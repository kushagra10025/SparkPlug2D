#pragma once

#include <memory>
#include <SP2DWindowing/Inputs/Keyboard.h>
#include <sol/sol.hpp>

namespace SP2D::Core::Scripting
{
	class InputManager
	{
	private:
		std::unique_ptr<SP2D::Windowing::Inputs::Keyboard> m_pKeyboard;

	private:
		InputManager();
		~InputManager() = default;
		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;

	private:
		static void RegisterLuaKeyNames(sol::state& lua);

	public:
		static InputManager& GetInstance();
		static void CreateLuaInputBindings(sol::state& lua);

		inline SP2D::Windowing::Inputs::Keyboard& GetKeyboard() { return *m_pKeyboard; }
	};
}