#include "ls.h" 

#include "System/Memory/MemoryManager.h"

#include <Windows.h>

namespace lumos {

	namespace internal {

		namespace memory {

			SystemMemoryInformation MemoryManager::GetSystemInformation()
			{
				MEMORYSTATUSEX status;
				status.dwLength = sizeof(MEMORYSTATUSEX);
				GlobalMemoryStatusEx(&status);

				SystemMemoryInformation result =
				{
					(int64)status.ullAvailPhys,
					(int64)status.ullTotalPhys,

					(int64)status.ullAvailVirtual,
					(int64)status.ullTotalVirtual
				};
				return result;
			}

		}

	}

}