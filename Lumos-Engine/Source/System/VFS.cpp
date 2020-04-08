#include "ls.h" 

#include "VFS.h"

namespace lumos {

	namespace internal {

		VFS* VFS::s_instance = nullptr;

		void VFS::Initialize()
		{
			s_instance = lsnew VFS();
		}

		void VFS::Shutdown()
		{
			lsdel s_instance;
		}

		void VFS::Mount(const String& virtualPath, const String& physicalPath)
		{
			LS_ASSERT(s_instance);
			m_mountPoints[virtualPath].push_back(physicalPath);
		}

		void VFS::Unmount(const String& path)
		{
			LS_ASSERT(s_instance);
			m_mountPoints[path].clear();
		}

		bool VFS::ResolvePhysicalPath(const String& path, String& outPhysicalPath)
		{
			if (path[0] != '/')
			{
				outPhysicalPath = path;
				return FileSystem::FileExists(path);
			}

			std::vector<String> dirs = SplitString(path, '/');
			const String& virtualDir = dirs.front();

			if (m_mountPoints.find(virtualDir) == m_mountPoints.end() || m_mountPoints[virtualDir].empty())
				return false;

			String remainder = path.substr(virtualDir.size() + 1, path.size() - virtualDir.size());
			for (const String& physicalPath : m_mountPoints[virtualDir])
			{
				String path = physicalPath + remainder;
				if (FileSystem::FileExists(path))
				{
					outPhysicalPath = path;
					return true;
				}
			}
			return false;
		}

		byte* VFS::ReadFile(const String& path)
		{
			LS_ASSERT(s_instance);
			String physicalPath;
			return ResolvePhysicalPath(path, physicalPath) ? FileSystem::ReadFile(physicalPath) : nullptr;
		}

		String VFS::ReadTextFile(const String& path)
		{
			LS_ASSERT(s_instance);
			String physicalPath;
			return ResolvePhysicalPath(path, physicalPath) ? FileSystem::ReadTextFile(physicalPath) : nullptr;
		}

		bool VFS::WriteFile(const String& path, byte* buffer)
		{
			LS_ASSERT(s_instance);
			String physicalPath;
			return ResolvePhysicalPath(path, physicalPath) ? FileSystem::WriteFile(physicalPath, buffer) : false;

		}

		bool VFS::WriteTextFile(const String& path, const String& text)
		{
			LS_ASSERT(s_instance);
			String physicalPath;
			return ResolvePhysicalPath(path, physicalPath) ? FileSystem::WriteTextFile(physicalPath, text) : false;
		}

	}

}