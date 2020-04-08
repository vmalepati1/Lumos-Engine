#pragma once

#include "ls.h"

#include "Core/String.h"

namespace lumos {

	namespace internal {

		namespace memory {

			struct LS_API SystemMemoryInformation {
				int64 availablePhysicalMemory;
				int64 totalPhysicalMemory;

				int64 availableVirtualMemory;
				int64 totalVirtualMemory;

				void Log();
			};

			struct LS_API MemoryUsage {
				int64 totalAllocated;
				int64 totalFreed;
				int64 currentUsed;
				int64 totalAllocations;

				MemoryUsage()
					: totalAllocated(0), totalFreed(0), currentUsed(0), totalAllocations(0)
				{
				}
			};

			class LS_API MemoryManager
			{

			public:

				MemoryManager();

				static void Initialize();
				static void Shutdown();

				static MemoryManager* Get();
				inline MemoryUsage GetMemoryStats() const { return m_memoryUsage; }

			public:

				SystemMemoryInformation GetSystemInformation();

			public:

				static String BytesToString(int64 bytes);

			public:

				static MemoryManager *s_instance;

			public:

				MemoryUsage m_memoryUsage;
			};

		}

	}

}