#pragma once

#include "ls.h"

#include "Types.h"

typedef std::string String;

namespace lumos {

#define STRINGFORMAT_BUFFER_SIZE 10 * 1024

	class LS_API StringFormat
	{
	private:
		static char s_buffer[STRINGFORMAT_BUFFER_SIZE];
	public:
		template<typename T>
		static String Hex(const T& input)
		{
			memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
			sprintf(s_buffer, "%02x", input);
			return String(s_buffer);
		}

		template<typename T>
		static String Hex(const T* input, uint size)
		{
			memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
			for (uint i = 0; i < size; i++)
				sprintf(s_buffer + i * 3, "%02x ", input[i]);
			return String(s_buffer);
		}

		static String Float(const float input, uint places = 2)
		{
			memset(s_buffer, 0, STRINGFORMAT_BUFFER_SIZE);
			sprintf(s_buffer, "%.2f", input);
			return String(s_buffer);
		}

		template<typename T>
		static String ToString(const T& input)
		{
			return std::to_string(input);
		}
	};

	std::vector<String> SplitString(const String& string, const String& delimiters);
	std::vector<String> SplitString(const String& string, const char delimiter);
	std::vector<String> Tokenize(const String& string);
	std::vector<String> GetLines(const String& string);

	const char* FindToken(const char* str, const String& token);
	const char* FindToken(const String& string, const String& token);
	int32 FindStringPosition(const String& string, const String& search, uint offset = 0);
	String StringRange(const String& string, uint start, uint length);
	String RemoveStringRange(const String& string, uint start, uint length);

	String GetBlock(const char* str, const char** outPosition = nullptr);
	String GetBlock(const String& string, uint offset = 0);

	String GetStatement(const char* str, const char** outPosition = nullptr);

	bool StringContains(const String& string, const String& chars);
	bool StartsWith(const String& string, const String& start);
	int32 NextInt(const String& string);

}