#include "ls.h" 

#include "Pool.h"

namespace lumos {

	namespace internal {

		namespace memory {

			StandardMemoryPool::StandardMemoryPool(size_t size) {
				uint _size = size + sizeof(Chunk);

				m_poolMemory = lsnew byte[_size];

				m_freePoolSize = _size - sizeof(Chunk);
				m_totalPoolSize = _size;

				Chunk freeChunk(_size - sizeof(Chunk));
				freeChunk.Write(m_poolMemory);
			}

			StandardMemoryPool::~StandardMemoryPool() {
				lsdel[] m_poolMemory;
			}

		}

	}

}