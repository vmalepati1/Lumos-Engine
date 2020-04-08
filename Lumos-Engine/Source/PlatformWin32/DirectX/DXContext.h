#pragma once

#include "Graphics/API/Context.h"

#include "DXInclude.h"

namespace lumos {

	namespace graphics {

		namespace API {

			class LS_API D3DContext : public Context {

			public:

				D3DContext(platform::WindowProperties properties, void *deviceContext);

				void Present();

			public:

				inline static D3DContext* GetContext() { return (D3DContext*)s_context; }

				inline static IDXGISwapChain* GetSwapChain() { return GetContext()->swapchain; }
				inline static ID3D11Device* GetDevice() { return GetContext()->dev; }
				inline static ID3D11DeviceContext* GetDeviceContext() { return GetContext()->devcon; }
				inline static ID3D11RenderTargetView* GetBackBuffer() { return GetContext()->m_renderTargetView; }

				inline static ID3D11DepthStencilView* GetDepthStencilBuffer() { return GetContext()->m_depthStencilView; }

				inline static String GetD3DVersionString() { return Get()->GetD3DVersionStringInternal(); }

			public:

				inline static D3DContext* Get() { return (D3DContext*)s_context; }

			public:

				IDXGISwapChain* swapchain;
				ID3D11Device* dev;
				ID3D11DeviceContext* devcon;
				ID3D11RenderTargetView* backbuffer;

			private:

				void InitD3D(HWND hWnd);
				void Resize();

				void SetRenderTargets(ID3D11RenderTargetView* target, ID3D11DepthStencilView* view);

				String GetD3DVersionStringInternal() const;

			private:

				D3D_FEATURE_LEVEL m_D3DFeatureLevel;
				uint m_MSAAQuality;
				bool m_MSAAEnabled;
				bool m_debugLayerEnabled;

				ID3D11RenderTargetView* m_renderTargetView;
				ID3D11DepthStencilView* m_depthStencilView;
				D3D11_VIEWPORT m_screenViewport;
				ID3D11Texture2D* m_depthStencilBuffer;

				ID3D11Debug* m_debugLayer;

				platform::WindowProperties m_properties;
			};

		}

	}

}