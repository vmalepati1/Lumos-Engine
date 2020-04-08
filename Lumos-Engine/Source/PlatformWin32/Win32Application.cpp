#include "ls.h"

#include "Platform/Application.h"

namespace lumos {

	namespace platform {

		Application::Application(const String& name, const WindowProperties& properties)
			: m_name(name), m_properties(properties), m_frametime(0.0f)
		{
			s_instance = this;
		}

		Application::~Application()
		{
			lsdel window;
			lsdel m_timer;

			internal::System::Shutdown();
		}

		void Application::PlatformInitialize()
		{
			window = lsnew Window(m_name, m_properties);
			window->SetEventCallback(METHOD(&Application::OnEvent));
		}

		void Application::Start()
		{
			Initialize();
			m_running = true;
			m_suspended = false;
			Run();
		}

		void Application::Suspend()
		{
			m_suspended = true;
		}

		void Application::Resume()
		{
			m_suspended = false;
		}

		void Application::Stop()
		{
			m_running = false;
		}

		void Application::Run()
		{
			m_timer = lsnew Timer();
			float timer = 0.0f;
			float updateTimer = m_timer->ElapsedMillis();
			float updateTick = 1000.0f / 60.0f;
			uint frames = 0;
			uint updates = 0;
			Timestep timestep(m_timer->ElapsedMillis());
			while (m_running)
			{
				window->Clear();
				float now = m_timer->ElapsedMillis();
				if (now - updateTimer > updateTick)
				{
					timestep.Update(now);
					OnUpdate(timestep);
					updates++;
					updateTimer += updateTick;
				}
				{
					Timer frametime;
					OnRender();
					frames++;
					m_frametime = frametime.ElapsedMillis();
				}
				window->Update();
				if (m_timer->Elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_framesPerSecond = frames;
					m_updatesPerSecond = updates;
					frames = 0;
					updates = 0;
					OnTick();
				}
				if (window->Closed())
					m_running = false;
			}
		}

		String Application::GetPlatform()
		{
#if defined(LS_PLATFORM_WIN32)
			return "Win32";
#elif defined(LS_PLATFORM_WIN64)
			return "Win64";
#else
			return "Unknown Platform";
#endif
		}

	}

}