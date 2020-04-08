#pragma once

#include "ls.h"
#include "Core/String.h"
#include "Core/Log.h"
#include "Events//Events.h"

#include "Input.h"

namespace lumos {

	namespace platform {

		typedef std::function<void(events::Event& event)> WindowEventCallback;

		struct LS_API WindowProperties {
			uint width, height;
			bool fullscreen;
			bool vsync;
		};

		class LS_API Window {
		public:

			Window(const String &title, const WindowProperties &properties);
			~Window();

			void Update();
			void Clear() const;
			bool Closed() const;

			void SetTitle(const String &title);

			inline uint GetWidth() const { return m_properties.width; }
			inline uint GetHeight() const { return m_properties.height; }

			inline InputManager* GetInputManager() const { return m_inputManager; }

			void SetEventCallback(const WindowEventCallback& callback);
		public:

			static void RegisterWindowClass(void *handle, Window *window);
			static Window *GetWindowClass(void *handle);

		private:

			bool Initialize();

			bool PlatformInitialize();
			void PlatformUpdate();
			void PlatformClean();

			friend void ResizeCallback(Window* window, int32 width, int32 height);
			friend void FocusCallback(Window* window, bool focused);

		private:

			static std::map<void *, Window *> s_handles;

		private:

			String m_title;
			WindowProperties m_properties;
			bool m_closed;
			void *m_handle;

			WindowEventCallback m_eventCallback;
			InputManager *m_inputManager;
		};

	}

}