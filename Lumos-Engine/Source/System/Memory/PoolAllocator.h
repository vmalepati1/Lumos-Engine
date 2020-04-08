#pragma once

#include "ls.h"

#include "IAllocator.h"
#include "Pool.h"

namespace lumos {

	namespace internal {

		namespace memory {

			class LS_API PoolAllocator : public IAllocator {
			public:

				PoolAllocator(MemoryPool &pool);

				void *Allocate(size_t size) override;
				void Free(void *pointer) override;

			private:
				
				MemoryPool *m_pool;
			};

		}

	}

}