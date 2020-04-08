#pragma once

#include "ls.h"

#include "Memory.h"

#include "Core/Log.h"

namespace lumos {

	namespace internal {

		namespace memory {

			class LS_API MemoryPool {
			public:

				inline virtual void *Allocate(size_t size) = 0;
				inline virtual void Free(void *pointer) = 0;
				inline virtual bool IntegrityCheck() const = 0;
				
				inline size_t GetTotalPoolSize() const { return m_totalPoolSize; }
				inline size_t GetFreePoolSize() const { return m_freePoolSize; }
			
			protected:

				MemoryPool()
					: m_totalPoolSize(0), m_freePoolSize(0) 
				{

				}

				size_t m_totalPoolSize;
				size_t m_freePoolSize;

			};

			class LS_API StandardMemoryPool : public MemoryPool {
			public:

				StandardMemoryPool(size_t size);
				~StandardMemoryPool();

				inline void *Allocate(size_t size) override {
					size_t requiredSize = size + sizeof(Chunk);

					Chunk *block = (Chunk *)(m_poolMemory);
					while (block)
					{
						if (block->free && block->userDataSize >= requiredSize) break;
						block = block->next;
					}

					byte *blockData = (byte *)(block);

					if (!block) return nullptr;

					size_t freeUserDataSize = block->userDataSize - requiredSize;
					if (freeUserDataSize > s_minimumFreeBlockSize) {
						Chunk freeBlock(freeUserDataSize);
						freeBlock.next = block->next;
						freeBlock.previous = block;
						freeBlock.Write(blockData + requiredSize);
						if (freeBlock.next) {
							freeBlock.next->previous = (Chunk *)(blockData + requiredSize);
						}
						block->next = (Chunk *)(blockData + requiredSize);
						block->userDataSize = size;
					}

					m_freePoolSize -= block->userDataSize;

					block->free = false;

					return (blockData + sizeof(Chunk));
				}

				inline void Free(void *pointer) override {
					if (!pointer) return;

					Chunk *block = (Chunk *)((byte *)pointer - sizeof(Chunk));
					LS_ASSERT(block->free == false, "This block of memory is already free!");

					size_t fullBlockSize = block->userDataSize + sizeof(Chunk);
					m_freePoolSize += block->userDataSize;

					Chunk *headBlock = block;
					Chunk *previous = block->previous;
					Chunk *next = block->next;

					if (block->previous && block->previous->free) {
						headBlock = block->previous;
						previous = block->previous->previous;
						next = block->next;

						fullBlockSize += block->previous->userDataSize + sizeof(Chunk);

						if (block->next) {
							block->next->previous = headBlock;

							if (block->next->free)
							{
								next = block->next->next;
								if (block->next->next)
									block->next->next->previous = headBlock;

								fullBlockSize += block->next->userDataSize + sizeof(Chunk);
							}
						}
					}
					else {
						if (block->next && block->next->free)
						{
							headBlock = block;
							previous = block->previous;
							next = block->next->next;

							fullBlockSize += block->next->userDataSize + sizeof(Chunk);
						}
					}

					byte *freeBlockStart = (byte *)(headBlock);

					size_t freeUserDataSize = fullBlockSize - sizeof(Chunk);

					Chunk freeBlock(freeUserDataSize);
					freeBlock.previous = previous;
					freeBlock.next = next;
					freeBlock.Write(freeBlockStart);
				}

				inline bool IntegrityCheck() const override {
					return true;
				}

				static const byte s_minimumFreeBlockSize = 16;

			private:

				struct Chunk {
					Chunk(size_t _userDataSize)
						: next(nullptr), previous(nullptr), userDataSize(_userDataSize), free(true)
					{

					}

					void Write(void *destination) {
						memcpy(destination, this, sizeof(Chunk));
					}

					void Read(void *source) {
						memcpy(this, source, sizeof(Chunk));
					}

					Chunk *next;
					Chunk *previous;
					size_t userDataSize;
					bool free;
				};

				byte *m_poolMemory;
			};

		}

	}

}