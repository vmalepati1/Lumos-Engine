#include "ls.h" 

#include "Core/Log.h"

#include <Windows.h>

namespace lumos {

	namespace core {

		void PlatformLogMessage(uint level, const char* message)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (level)
			{
			case LUMOS_LOG_LEVEL_FATAL:
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case LUMOS_LOG_LEVEL_ERROR:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case LUMOS_LOG_LEVEL_WARNING:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
			printf("%s", message);
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}

	}

}