#include "ls.h" 

#include "MemoryManager.h"

#include "Core/Log.h"

#include "Memory.h"

namespace lumos {

	namespace internal {

		namespace memory {

			MemoryManager* MemoryManager::s_instance = nullptr;

			MemoryManager::MemoryManager()
			{
			}

			void MemoryManager::Initialize()
			{
			}

			void MemoryManager::Shutdown()
			{
				free(s_instance);
			}

			MemoryManager* MemoryManager::Get()
			{
				if (s_instance == nullptr)
				{
					s_instance = (MemoryManager*)malloc(sizeof(MemoryManager));
					s_instance = lsnew(s_instance) MemoryManager();
				}

				return s_instance;
			}

			String MemoryManager::BytesToString(int64 bytes)
			{
				static const float gb = 1024 * 1024 * 1024;
				static const float mb = 1024 * 1024;
				static const float kb = 1024;

				String result;
				if (bytes > gb)
					result = StringFormat::Float(bytes / gb) + " GB";
				else if (bytes > mb)
					result = StringFormat::Float(bytes / mb) + " MB";
				else if (bytes > kb)
					result = StringFormat::Float(bytes / kb) + " KB";
				else
					result = StringFormat::Float((float)bytes) + " bytes";

				return result;
			}

			void SystemMemoryInformation::Log()
			{
				String apm, tpm, avm, tvm;

				uint gb = 1024 * 1024 * 1024;
				uint mb = 1024 * 1024;
				uint kb = 1024;

				apm = MemoryManager::BytesToString(availablePhysicalMemory);
				tpm = MemoryManager::BytesToString(totalPhysicalMemory);
				avm = MemoryManager::BytesToString(availableVirtualMemory);
				tvm = MemoryManager::BytesToString(totalVirtualMemory);

				LS_INFO();
				LS_INFO("Memory Info:");
				LS_INFO("\tPhysical Memory (Avail/Total): ", apm, " / ", tpm);
				LS_INFO("\tVirtual Memory  (Avail/Total): ", avm, " / ", tvm);
				LS_INFO();
			}

		}

	}

}