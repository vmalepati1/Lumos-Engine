#pragma once

#include "ls.h"

#include "Core/String.h"

namespace lumos {

	namespace graphics {

		namespace API {

			class LS_API Shader {

			public:

				static Shader *CreateFromSource(const String &name, const String &source);
				static Shader *CreateFromFile(const String &name, const String &filepath);
			};

		}

	}

}