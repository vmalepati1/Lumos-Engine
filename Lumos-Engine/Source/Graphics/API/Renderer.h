#pragma once

#include "ls.h"

#include "Core/String.h"

namespace lumos {

	namespace graphics {

		namespace API {

			enum LS_API RendererBufferType
			{
				RENDERER_BUFFER_NONE = 0,
				RENDERER_BUFFER_COLOR = BIT(0),
				RENDERER_BUFFER_DEPTH = BIT(1),
				RENDERER_BUFFER_STENCIL = BIT(2)
			};

			enum class LS_API RendererBlendFunction
			{
				NONE,
				ZERO,
				ONE,
				SOURCE_ALPHA,
				DESTINATION_ALPHA,
				ONE_MINUS_SOURCE_ALPHA
			};

			enum class LS_API RendererBlendEquation
			{
				NONE,
				ADD,
				SUBTRACT
			};

			class LS_API Renderer
			{

			protected:

				virtual void InitializeInternal() = 0;

				virtual void ClearInternal(uint buffer) = 0;
				virtual void PresentInternal() = 0;

				virtual void SetDepthTestingInternal(bool enabled) = 0;
				virtual void SetBlendInternal(bool enabled) = 0;
				virtual void SetViewportInternal(uint x, uint y, uint width, uint height) = 0;

				virtual void SetBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) = 0;
				virtual void SetBlendEquationInternal(RendererBlendFunction blendEquation) = 0;

				virtual const String& GetTitleInternal() const = 0;

			public:
				inline static void Clear(uint buffer) { s_instance->ClearInternal(buffer); }
				inline static void Present() { s_instance->PresentInternal(); }

				inline static void SetDepthTesting(bool enabled) { s_instance->SetDepthTestingInternal(enabled); }
				inline static void SetBlend(bool enabled) { s_instance->SetBlendInternal(enabled); }
				inline static void SetViewport(uint x, uint y, uint width, uint height) { s_instance->SetViewportInternal(x, y, width, height); }

				inline static void SetBlendFunction(RendererBlendFunction source, RendererBlendFunction destination) { s_instance->SetBlendFunctionInternal(source, destination); }
				inline static void SetBlendEquation(RendererBlendFunction blendEquation) { s_instance->SetBlendEquationInternal(blendEquation); }

				inline static const String& GetTitle() { return s_instance->GetTitleInternal(); }

			public:

				static void Initialize();
				static void Shutdown();

				inline static Renderer* GetRenderer() { return s_instance; }

			private:

				static Renderer* s_instance;
			};

		}

	}

}