#pragma once

#include "Window.h"
#include "Timer.h"
#include "Timestep.h"

#include "System/System.h"
#include "System/Memory/Memory.h"

namespace lumos {

	namespace platform {

		class LS_API Application {

		public:

			Application(const String &name, const WindowProperties &properties);
			virtual ~Application();

			virtual void Initialize();

			void Start();
			void Suspend();
			void Resume();
			void Stop();

			inline uint GetFPS() const { return m_framesPerSecond; }
			inline uint GetUPS() const { return m_updatesPerSecond; }

			inline uint GetWindowWidth() const { return window->GetWidth(); }
			inline uint GetWindowHeight() const { return window->GetHeight(); }
			inline maths::Vec2 GetWindowSize() const { return maths::Vec2((float)window->GetWidth(), (float)window->GetHeight()); }

			String GetBuildConfiguration();
			String GetPlatform();

		public:

			inline static Application& GetApplication() { return *s_instance; }

		public:

			Window* window;

		private:

			void OnEvent(events::Event& event);

		private:

			void PlatformInitialize();
			void Run();

			void OnTick();
			void OnUpdate(const Timestep& ts);
			void OnRender();

		private:

			static Application* s_instance;;

		private:

			bool m_running, m_suspended;
			Timer* m_timer;
			uint m_updatesPerSecond, m_framesPerSecond;
			float m_frametime;

			String m_name;
			WindowProperties m_properties;
		};

	}

}