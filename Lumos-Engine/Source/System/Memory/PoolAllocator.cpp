#include "ls.h" 

#include "PoolAllocator.h"

namespace lumos {

	namespace internal {

		namespace memory {

			PoolAllocator::PoolAllocator(MemoryPool &pool)
				: m_pool(&pool)
			{

			}

			void *PoolAllocator::Allocate(size_t size) {
				return m_pool->Allocate(size);
			}

			void PoolAllocator::Free(void *pointer) {
				m_pool->Free(pointer);
			}

		}

	}

}