#include "ls.h"

#include "DXRenderer.h"

#include "System/Memory/Memory.h"
#include "System/Memory/MemoryManager.h"

namespace lumos {

	namespace graphics {

		namespace API {

			Renderer* Renderer::s_instance = nullptr;

			std::vector<ID3D11BlendState*> D3DRenderer::s_blendStates;
			std::vector<ID3D11DepthStencilState*> D3DRenderer::s_depthStencilStates;

			void Renderer::Initialize() {
				s_instance = lsnew D3DRenderer();
				s_instance->InitializeInternal();
			}

			void Renderer::Shutdown() {
				SAFE_DELETE(s_instance);
			}

			D3DRenderer::D3DRenderer()
			{
				m_context = D3DContext::Get();
			}

			void D3DRenderer::InitializeInternal()
			{
				CreateBlendStates();
				CreateDepthStencilStates();

				SetDepthTesting(true);
				SetBlendFunction(RendererBlendFunction::SOURCE_ALPHA, RendererBlendFunction::ONE_MINUS_SOURCE_ALPHA);
				SetBlend(true);

				IDXGIDevice* dxgiDev;
				D3DContext::GetDevice()->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDev);
				IDXGIAdapter* adapter;
				dxgiDev->GetAdapter(&adapter);
				DXGI_ADAPTER_DESC desc;
				adapter->GetDesc(&desc);
				LS_WARNING("----------------------------------");
				LS_WARNING(" Direct3D ", D3DContext::GetD3DVersionString(), ":");
				LS_WARNING("    ", desc.Description);
				LS_WARNING("    ", "VRAM: ", internal::memory::MemoryManager::BytesToString(desc.DedicatedVideoMemory));
				LS_WARNING("----------------------------------");

				m_rendererTitle = "Direct3D " + D3DContext::GetD3DVersionString();
			}

			void D3DRenderer::CreateBlendStates()
			{
				{
					D3D11_BLEND_DESC desc;
					ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
					desc.RenderTarget[0].BlendEnable = false;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					ID3D11BlendState* state;
					DXCheck(D3DContext::GetDevice()->CreateBlendState(&desc, &state));
					s_blendStates.push_back(state);
				}
				{
					D3D11_BLEND_DESC desc;
					ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
					desc.AlphaToCoverageEnable = false;
					desc.IndependentBlendEnable = false;

					desc.RenderTarget[0].BlendEnable = true;

					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
					desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
					desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					ID3D11BlendState* state;
					DXCheck(D3DContext::GetDevice()->CreateBlendState(&desc, &state));
					s_blendStates.push_back(state);
				}
			}

			void D3DRenderer::CreateDepthStencilStates()
			{
				{
					D3D11_DEPTH_STENCIL_DESC desc;
					desc.DepthEnable = true;
					desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
					desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
					desc.StencilEnable = true;
					desc.StencilReadMask = 0xff;
					desc.StencilWriteMask = 0xff;

					desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;
					desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

					desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;

					ID3D11DepthStencilState* state;
					DXCheck(D3DContext::GetDevice()->CreateDepthStencilState(&desc, &state));
					s_depthStencilStates.push_back(state);
				}
				{
					D3D11_DEPTH_STENCIL_DESC desc;
					desc.DepthEnable = false;
					desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
					desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
					desc.StencilEnable = true;
					desc.StencilReadMask = 0xff;
					desc.StencilWriteMask = 0xff;

					desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;
					desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

					desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;

					ID3D11DepthStencilState* state;
					DXCheck(D3DContext::GetDevice()->CreateDepthStencilState(&desc, &state));
					s_depthStencilStates.push_back(state);
				}
			}

			void D3DRenderer::ClearInternal(uint buffer)
			{
				float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

				if (buffer & RendererBufferType::RENDERER_BUFFER_COLOR)
					D3DContext::GetDeviceContext()->ClearRenderTargetView(D3DContext::GetBackBuffer(), color);
				if (buffer & RendererBufferType::RENDERER_BUFFER_DEPTH)
					D3DContext::GetDeviceContext()->ClearDepthStencilView(D3DContext::GetDepthStencilBuffer(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
			}

			void D3DRenderer::PresentInternal()
			{
				m_context->Present();
			}

			void D3DRenderer::SetDepthTestingInternal(bool enabled)
			{
				D3DContext::GetDeviceContext()->OMSetDepthStencilState(enabled ? s_depthStencilStates[0] : s_depthStencilStates[1], NULL);
			}

			void D3DRenderer::SetBlendInternal(bool enabled)
			{
				D3DContext::GetDeviceContext()->OMSetBlendState(enabled ? s_blendStates[1] : s_blendStates[0], NULL, 0xffffffff);
			}

			void D3DRenderer::SetBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination)
			{

			}

			void D3DRenderer::SetBlendEquationInternal(RendererBlendFunction blendEquation)
			{

			}

			void D3DRenderer::SetViewportInternal(uint x, uint y, uint width, uint height)
			{

			}

			const String& D3DRenderer::GetTitleInternal() const
			{
				return m_rendererTitle;
			}

		}

	}

}