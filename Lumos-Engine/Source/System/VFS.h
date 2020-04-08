#pragma once

#include "ls.h"

#include "Core/String.h"

#include "FileSystem.h"

#include "System/Memory/Memory.h"

namespace lumos {

	namespace internal {

		class LS_API VFS
		{
		private:
			static VFS* s_instance;
		private:
			std::unordered_map<String, std::vector<String>> m_mountPoints;
		public:
			void Mount(const String& virtualPath, const String& physicalPath);
			void Unmount(const String& path);
			bool ResolvePhysicalPath(const String& path, String& outPhysicalPath);

			byte* ReadFile(const String& path);
			String ReadTextFile(const String& path);

			bool WriteFile(const String& path, byte* buffer);
			bool WriteTextFile(const String& path, const String& text);
		public:
			static void Initialize();
			static void Shutdown();

			inline static VFS* Get() { return s_instance; }
		};

	}

}