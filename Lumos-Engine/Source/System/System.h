#pragma once

#include "System/Memory/MemoryManager.h"

#include "VFS.h"

#include "Core/Log.h"

namespace lumos {

	namespace internal {

		struct LS_API SystemInformation {
			memory::SystemMemoryInformation memoryInformation;
		};

		class LS_API System {
			
		public:

			static void Initialize();
			static void Shutdown();

			static SystemInformation GetSystemInformation();

		private:

			static void LogSystemInformation();

		private:

			static SystemInformation s_systemInformation;
		};

	}

}