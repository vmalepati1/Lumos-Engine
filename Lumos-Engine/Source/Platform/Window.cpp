#include "ls.h" 

#include "Window.h"
#include "Graphics/API/Context.h"
#include "Graphics/API/Renderer.h"

#include "System/Memory/Memory.h"

namespace lumos {

	namespace platform {

		using namespace graphics;
		using namespace API;

		std::map<void*, Window*> Window::s_handles;

		Window::Window(const String &title, const WindowProperties &properties) 
			: m_title(title), m_properties(properties), m_closed(false), m_handle(nullptr)
		{
			if (!Initialize()) {
				LS_ERROR("Failed base window initialization!");
				return;
			}

			m_inputManager = lsnew InputManager();
		}

		Window::~Window() {
			lsdel m_inputManager;

			Renderer::Shutdown();

			PlatformClean();
		}

		bool Window::Initialize() {
			if (!PlatformInitialize()) {
				LS_FATAL("Failed to initialize platform!");
				return false;
			}

			Renderer::Initialize();

			SetTitle(m_title);

			return true;
		}

		void Window::Clear() const {
			Renderer::Clear(RENDERER_BUFFER_COLOR | RENDERER_BUFFER_DEPTH);
		}

		void Window::Update() {
			PlatformUpdate();
		}

		bool Window::Closed() const {
			return m_closed;
		}

		void Window::SetEventCallback(const WindowEventCallback& callback)
		{
			m_eventCallback = callback;
			m_inputManager->SetEventCallback(m_eventCallback);
		}

		void Window::RegisterWindowClass(void* handle, Window* window)
		{
			s_handles[handle] = window;
		}

		Window* Window::GetWindowClass(void* handle)
		{
			if (handle == nullptr)
				return s_handles.begin()->second;

			return s_handles[handle];
		}

	}
}