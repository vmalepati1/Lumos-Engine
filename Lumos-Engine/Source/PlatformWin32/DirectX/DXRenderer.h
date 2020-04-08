#pragma once

#include "Graphics/API/Renderer.h"
#include "DXContext.h"

namespace lumos {

	namespace graphics {

		namespace API {

			class LS_API D3DRenderer : public Renderer
			{

			protected:

				void InitializeInternal() override;

				void ClearInternal(uint buffer) override;
				void PresentInternal() override;

				void SetDepthTestingInternal(bool enabled) override;
				void SetBlendInternal(bool enabled) override;
				void SetViewportInternal(uint x, uint y, uint width, uint height) override;

				void SetBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) override;
				void SetBlendEquationInternal(RendererBlendFunction blendEquation) override;

				const String& GetTitleInternal() const override;

			private:
				
				void CreateBlendStates();
				void CreateDepthStencilStates();

			private:

				static std::vector<ID3D11BlendState*> s_blendStates;
				static std::vector<ID3D11DepthStencilState*> s_depthStencilStates;

			private:

				API::D3DContext* m_context;
				String m_rendererTitle;

			public:

				D3DRenderer();
			};
		}

	}

}