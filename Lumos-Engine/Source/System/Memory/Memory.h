#pragma once

#include "StackAllocator.h"
#include "MemoryManager.h"

#define lsnew			new
#define lsdel			delete

#pragma warning(disable : 4595)

extern LS_API lumos::internal::memory::StackAllocator g_stackAllocator;

inline void* operator new(size_t size)
{
	return g_stackAllocator.Allocate(size);
}

inline void* operator new[](size_t size)
{
	return g_stackAllocator.Allocate(size);
}

inline void operator delete(void* pointer)
{
	g_stackAllocator.Free(pointer);
}

inline void operator delete[](void* pointer)
{
	g_stackAllocator.Free(pointer);
}

#pragma warning(default : 4595)