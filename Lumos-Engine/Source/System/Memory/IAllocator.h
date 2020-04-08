#pragma once

#include "ls.h"

namespace lumos {

	namespace internal {

		namespace memory {

			class LS_API IAllocator {
			protected:

				virtual void *Allocate(size_t size) = 0;
				virtual void Free(void *pointer) = 0;
			};

		}

	}

}