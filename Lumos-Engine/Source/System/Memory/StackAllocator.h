#pragma once

#include "ls.h"

#include "IAllocator.h"

#include "Core/Log.h"

namespace lumos {

	namespace internal {

		namespace memory {

			class LS_API StackAllocator : public IAllocator {
			public:

				void *Allocate(size_t size) override;
				void Free(void *pointer) override;
			};

		}

	}

}