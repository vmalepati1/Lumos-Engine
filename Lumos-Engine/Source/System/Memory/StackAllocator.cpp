#include "ls.h" 

#include "StackAllocator.h"

#include "MemoryManager.h"

namespace lumos {

#define LS_MEMORY_ALIGNMENT 16
#define LS_ALLOC(size)	_aligned_malloc(size, LS_MEMORY_ALIGNMENT)
#define LS_FREE(block)	_aligned_free(block);

	namespace internal {

		namespace memory {

			void *StackAllocator::Allocate(size_t size) {
				LS_ASSERT(size < 1024 * 1024 * 1024);

				MemoryManager::Get()->m_memoryUsage.totalAllocated += size;
				MemoryManager::Get()->m_memoryUsage.currentUsed += size;
				MemoryManager::Get()->m_memoryUsage.totalAllocations++;

				size_t actualSize = size + sizeof(size_t);
				byte *result = (byte*)LS_ALLOC(actualSize);
				memset(result, 0, actualSize);
				memcpy(result, &size, sizeof(size_t));
				result += sizeof(size_t);
				return result;
			}

			void StackAllocator::Free(void *pointer) {
				byte *memory = ((byte*)pointer) - sizeof(size_t);
				size_t size = *(size_t*)memory;

				MemoryManager::Get()->m_memoryUsage.totalFreed += size;
				MemoryManager::Get()->m_memoryUsage.currentUsed -= size;

				LS_FREE(memory);
			}

		}

	}

}