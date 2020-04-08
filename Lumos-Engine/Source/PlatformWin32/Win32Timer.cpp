#include "ls.h" 

#include "Platform/Timer.h"

#include "System/Memory/Memory.h"

#include <Windows.h>

namespace lumos {

	namespace platform {

		struct LS_API Members {
			LARGE_INTEGER m_start;
			double m_frequency;
		};

		Timer::Timer()
			: m_members(lsnew (m_reserved) Members())
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_members->m_frequency = 1.0 / frequency.QuadPart;

			Reset();
		}

		void Timer::Reset()
		{
			QueryPerformanceCounter(&m_members->m_start);
		}

		float Timer::Elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			uint64 cycles = current.QuadPart - m_members->m_start.QuadPart;
			return (float)(cycles * m_members->m_frequency);
		}

		float Timer::ElapsedMillis()
		{
			return Elapsed() * 1000.0f;
		}

	}

}