#pragma once

#include "ls.h"

#include "Platform/Window.h"

namespace lumos {

	namespace graphics {

		namespace API {

			class LS_API Context {

			public:

				static void Create(platform::WindowProperties properties, void *deviceContext);
				static void Destroy();
			
			protected:

				static Context *s_context;
			};

		}

	}

}