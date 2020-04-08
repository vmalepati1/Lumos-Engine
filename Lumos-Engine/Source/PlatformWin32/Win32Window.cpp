#include "ls.h" 

#include "Platform/Window.h"
#include "Platform/Application.h"

#define NOMINMAX
#undef NOGDI
#include <Windows.h>
#include <Windowsx.h>
#define NOGDI

#include "Graphics/API/Context.h"
#include "Graphics/API/Renderer.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace lumos {

	namespace platform {

		using namespace events;
		using namespace graphics;
		using namespace API;


		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		extern void MouseButtonCallback(InputManager* inputManager, int32 button, int32 x, int32 y);
		extern void KeyCallback(InputManager* inputManager, int32 flags, int32 key, uint message);

		HINSTANCE hInstance;
		HDC hDc;
		HWND hWnd;

		static PIXELFORMATDESCRIPTOR GetPixelFormat()
		{
			PIXELFORMATDESCRIPTOR result = {};
			result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			result.nVersion = 1;
			result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			result.iPixelType = PFD_TYPE_RGBA;
			result.cColorBits = 32;
			result.cDepthBits = 24;
			result.cStencilBits = 8;
			result.cAuxBuffers = 0;
			result.iLayerType = PFD_MAIN_PLANE;
			return result;
		}

		bool Window::PlatformInitialize() {
			hInstance = (HINSTANCE)&__ImageBase;

			WNDCLASS winClass = {};
			winClass.hInstance = hInstance; // GetModuleHandle(0);
			winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			winClass.lpfnWndProc = (WNDPROC)WndProc;
			winClass.lpszClassName = "Lumos Win32 Window";
			winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);

			if (!RegisterClassA(&winClass))
			{
				LS_ERROR("Could not register Win32 class!");
				return false;
			}

			RECT size = { 0, 0, (LONG)m_properties.width, (LONG)m_properties.height };
			AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

			hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
				winClass.lpszClassName, m_title.c_str(),
				WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
				GetSystemMetrics(SM_CXSCREEN) / 2 - m_properties.width / 2,
				GetSystemMetrics(SM_CYSCREEN) / 2 - m_properties.height / 2,
				size.right + (-size.left), size.bottom + (-size.top), NULL, NULL, hInstance, NULL);

			if (!hWnd)
			{
				LS_ERROR("Could not create window!");
				return false;
			}

			RegisterWindowClass(hWnd, this);

			hDc = GetDC(hWnd);
			PIXELFORMATDESCRIPTOR pfd = GetPixelFormat();
			int32 pixelFormat = ChoosePixelFormat(hDc, &pfd);
			if (pixelFormat)
			{
				if (!SetPixelFormat(hDc, pixelFormat, &pfd))
				{
					LS_ERROR("Failed setting pixel format!");
					return false;
				}
			}
			else
			{
				LS_ERROR("Failed choosing pixel format!");
				return false;
			}

			Context::Create(m_properties, hWnd);

			ShowWindow(hWnd, SW_SHOW);
			SetFocus(hWnd);

			return true;
		}

		void Window::PlatformUpdate()
		{
			MSG message;
			while (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE) > 0)
			{
				if (message.message == WM_QUIT)
				{
					m_closed = true;
					return;
				}
				TranslateMessage(&message);
				DispatchMessage(&message);
			}

			m_inputManager->PlatformUpdate();
			Renderer::Present();
		}

		void Window::PlatformClean() {
			Context::Destroy();
		}

		void Window::SetTitle(const String& title)
		{
			m_title = title + "  |  " + Application::GetApplication().GetBuildConfiguration() + " " + Application::GetApplication().GetPlatform() + "  |  Renderer: " + Renderer::GetTitle();
			SetWindowText(hWnd, m_title.c_str());
		}

		void ResizeCallback(Window* window, int32 width, int32 height)
		{
			window->m_properties.width = width;
			window->m_properties.height = height;

			if (window->m_eventCallback)
				window->m_eventCallback(ResizeWindowEvent((uint)width, (uint)height));
		}

		void FocusCallback(Window* window, bool focused)
		{
			if (!focused)
			{
				window->m_inputManager->ClearKeys();
				window->m_inputManager->ClearMouseButtons();
			}
		}

		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			LRESULT result = NULL;
			Window* window = Window::GetWindowClass(hWnd);
			if (window == nullptr)
				return DefWindowProc(hWnd, message, wParam, lParam);

			InputManager* inputManager = window->GetInputManager();
			switch (message)
			{
			case WM_ACTIVATE:
			{
				if (!HIWORD(wParam)) // Is minimized
				{
					// active
				}
				else
				{
					// inactive
				}

				return 0;
			}
			case WM_SYSCOMMAND:
			{
				switch (wParam)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
				}
				result = DefWindowProc(hWnd, message, wParam, lParam);
			} break;
			case WM_SETFOCUS:
				FocusCallback(window, true);
				break;
			case WM_KILLFOCUS:
				FocusCallback(window, false);
				break;
			case WM_CLOSE:
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				KeyCallback(inputManager, lParam, wParam, message);
				break;
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
				MouseButtonCallback(inputManager, message, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;
			case WM_SIZE:
				ResizeCallback(window, LOWORD(lParam), HIWORD(lParam));
				break;
			default:
				result = DefWindowProc(hWnd, message, wParam, lParam);
			}
			return result;
		}

	}

}