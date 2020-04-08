#include "ls.h" 

#include "Application.h"

namespace lumos {

	namespace platform {

		Application* Application::s_instance = nullptr;

		void Application::Initialize() {
			internal::System::Initialize();

			PlatformInitialize();
		}

		void Application::OnEvent(events::Event& event)
		{
			if (event.IsHandled())
				return;
		}

		void Application::OnTick()
		{

		}

		void Application::OnUpdate(const Timestep& ts)
		{

		}

		void Application::OnRender()
		{

		}

		String Application::GetBuildConfiguration()
		{
#if defined(LS_DEBUG)
			return "Debug";
#elif defined(LS_RELEASE)
			return "Release";
#else
			return "Unknown Build Configuration";
#endif
		}

	}

}