#include "ls.h" 

#include "Platform/Input.h"
#include "Core/Log.h"

#include <Windows.h>
#include <Windowsx.h>

#include "Platform/Window.h"
#include "Events/Events.h"

namespace lumos {

	namespace platform {

		using namespace events;

		extern HWND hWnd;

		void InputManager::PlatformUpdate()
		{
			POINT mouse;
			GetCursorPos(&mouse);
			ScreenToClient(hWnd, &mouse);

			maths::Vec2 mousePos = maths::Vec2((float)mouse.x, (float)mouse.y);
			if (mousePos != m_mousePosition)
			{
				m_eventCallback(MouseMovedEvent(mousePos.x, mousePos.y, m_mouseButtons[LS_MOUSE_LEFT]));
				m_mousePosition = mousePos;
			}
		}

		void InputManager::SetMousePosition(const maths::Vec2& position)
		{
			POINT pt = { (LONG)position.x, (LONG)position.y };
			ClientToScreen(hWnd, &pt);
			SetCursorPos(pt.x, pt.y);
		}

		void InputManager::SetMouseCursor(int32 cursor)
		{
			if (cursor == LS_NO_CURSOR)
			{
				SetCursor(LS_NO_CURSOR);
				while (ShowCursor(false) >= 0);
			}
			else
			{
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				ShowCursor(true);
			}
		}

		void KeyCallback(InputManager* inputManager, int32 flags, int32 key, uint message)
		{
			bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
			inputManager->m_keyState[key] = pressed;

			bool repeat = (flags >> 30) & 1;

			int32 modifier = 0;
			switch (key)
			{
			case LS_KEY_CONTROL:
				modifier = LS_MODIFIER_LEFT_CONTROL;
				break;
			case LS_KEY_ALT:
				modifier = LS_MODIFIER_LEFT_ALT;
				break;
			case LS_KEY_SHIFT:
				modifier = LS_MODIFIER_LEFT_SHIFT;
				break;
			}
			if (pressed)
				inputManager->m_keyModifiers |= modifier;
			else
				inputManager->m_keyModifiers &= ~(modifier);

			if (pressed)
				inputManager->m_eventCallback(KeyPressedEvent(key, repeat, inputManager->m_keyModifiers));
			else
				inputManager->m_eventCallback(KeyReleasedEvent(key));
		}

		void MouseButtonCallback(InputManager* inputManager, int32 button, int32 x, int32 y)
		{
			bool down = false;
			switch (button)
			{
			case WM_LBUTTONDOWN:
				SetCapture(hWnd);
				button = LS_MOUSE_LEFT;
				down = true;
				break;
			case WM_LBUTTONUP:
				ReleaseCapture();
				button = LS_MOUSE_LEFT;
				down = false;
				break;
			case WM_RBUTTONDOWN:
				SetCapture(hWnd);
				button = LS_MOUSE_RIGHT;
				down = true;
				break;
			case WM_RBUTTONUP:
				ReleaseCapture();
				button = LS_MOUSE_RIGHT;
				down = false;
				break;
			case WM_MBUTTONDOWN:
				SetCapture(hWnd);
				button = LS_MOUSE_MIDDLE;
				down = true;
				break;
			case WM_MBUTTONUP:
				ReleaseCapture();
				button = LS_MOUSE_MIDDLE;
				down = false;
				break;
			}
			inputManager->m_mouseButtons[button] = down;
			inputManager->m_mousePosition.x = (float)x;
			inputManager->m_mousePosition.y = (float)y;

			LS_ASSERT(inputManager->m_eventCallback);

			if (down)
				inputManager->m_eventCallback(MousePressedEvent(button, (float)x, (float)y));
			else
				inputManager->m_eventCallback(MouseReleasedEvent(button, (float)x, (float)y));
		}

	}

}