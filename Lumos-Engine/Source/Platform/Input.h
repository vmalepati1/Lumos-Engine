#pragma once

#include "ls.h"
#include "Maths/Maths.h"
#include "Events/Event.h"

namespace lumos {

	namespace platform {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

		typedef std::function<void(events::Event& event)> WindowEventCallback;

		class Window;

		class LS_API InputManager
		{
		public:

			InputManager();

			inline void SetEventCallback(const WindowEventCallback& eventCallback) { m_eventCallback = eventCallback; }

			void Update();
			void PlatformUpdate();

			bool IsKeyPressed(uint keycode) const;
			bool IsMouseButtonPressed(uint button) const;
			bool IsMouseButtonClicked(uint button) const;

			const maths::Vec2& GetMousePosition() const;
			void SetMousePosition(const maths::Vec2& position);
			const bool IsMouseGrabbed() const;
			void SetMouseGrabbed(bool grabbed);
			void SetMouseCursor(int32 cursor);

			void ClearKeys();
			void ClearMouseButtons();

		private:

			friend class Window;

		private:

			bool m_keyState[MAX_KEYS];
			bool m_lastKeyState[MAX_KEYS];

			bool m_mouseButtons[MAX_BUTTONS];
			bool m_mouseState[MAX_BUTTONS];
			bool m_mouseClicked[MAX_BUTTONS];
			bool m_mouseGrabbed;
			int32 m_keyModifiers;

			maths::Vec2 m_mousePosition;
			WindowEventCallback m_eventCallback;

		private:

			friend void KeyCallback(InputManager* inputManager, int32 flags, int32 key, uint message);
			friend void MouseButtonCallback(InputManager* inputManager, int32 button, int32 x, int32 y);
		};

		class LS_API Input
		{

		public:

			inline static bool IsKeyPressed(uint keycode) { return s_inputManager->IsKeyPressed(keycode); }
			inline static bool IsMouseButtonPressed(uint button) { return s_inputManager->IsMouseButtonPressed(button); }
			inline static bool IsMouseButtonClicked(uint button) { return s_inputManager->IsMouseButtonClicked(button); }

			inline static const maths::Vec2& GetMousePosition() { return s_inputManager->GetMousePosition(); }

			inline static InputManager* GetInputManager() { return s_inputManager; }

		private:

			friend class InputManager;

		private:

			static InputManager* s_inputManager;
		};

	}

}

#include "InputDefines.h"