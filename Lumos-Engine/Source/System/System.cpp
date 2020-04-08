#include "ls.h" 

#include "System.h"

namespace lumos {

	namespace internal {

		using namespace memory;

		SystemInformation System::s_systemInformation;

		void System::Initialize()
		{
			LS_INFO("Initializing Lumos System...");
			MemoryManager::Initialize();
			VFS::Initialize();

			s_systemInformation.memoryInformation = MemoryManager::Get()->GetSystemInformation();
			LogSystemInformation();
		}

		void System::Shutdown()
		{
			LS_INFO("Shutting down Lumos System...");
			MemoryManager::Shutdown();
			VFS::Shutdown();
		}

		SystemInformation System::GetSystemInformation()
		{
			return s_systemInformation;
		}

		void System::LogSystemInformation()
		{
			LS_INFO("--------------------");
			LS_INFO(" System Information ");
			LS_INFO("--------------------");
			s_systemInformation.memoryInformation.Log();
		}

	}

}