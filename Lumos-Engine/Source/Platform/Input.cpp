#include "ls.h" 

#include "Input.h"

namespace lumos {

	namespace platform {

		InputManager* Input::s_inputManager = nullptr;

		InputManager::InputManager()
		{
			ClearKeys();
			ClearMouseButtons();

			m_mouseGrabbed = true;

			Input::s_inputManager = this;
		}

		void InputManager::Update()
		{
			for (int32 i = 0; i < MAX_BUTTONS; i++)
				m_mouseClicked[i] = m_mouseButtons[i] && !m_mouseState[i];

			memcpy(m_lastKeyState, m_keyState, MAX_KEYS);
			memcpy(m_mouseState, m_mouseButtons, MAX_BUTTONS);
		}

		void InputManager::ClearKeys()
		{
			for (int32 i = 0; i < MAX_KEYS; i++)
			{
				m_keyState[i] = false;
				m_lastKeyState[i] = false;
			}
			m_keyModifiers = 0;
		}

		void InputManager::ClearMouseButtons()
		{
			for (int32 i = 0; i < MAX_BUTTONS; i++)
			{
				m_mouseButtons[i] = false;
				m_mouseState[i] = false;
				m_mouseClicked[i] = false;
			}
		}

		bool InputManager::IsKeyPressed(uint keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_keyState[keycode];
		}

		bool InputManager::IsMouseButtonPressed(uint button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return m_mouseButtons[button];
		}

		bool InputManager::IsMouseButtonClicked(uint button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return m_mouseClicked[button];
		}

		const maths::Vec2& InputManager::GetMousePosition() const
		{
			return m_mousePosition;
		}

		const bool InputManager::IsMouseGrabbed() const
		{
			return m_mouseGrabbed;
		}

		void InputManager::SetMouseGrabbed(bool grabbed)
		{
			m_mouseGrabbed = grabbed;
		}

	}

}