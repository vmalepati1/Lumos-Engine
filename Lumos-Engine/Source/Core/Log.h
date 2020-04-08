#pragma once

#include "Core.h"
#include "String.h"
#include "Types.h"

#include "Events/Events.h"

#define LUMOS_LOG_LEVEL_FATAL		0
#define LUMOS_LOG_LEVEL_ERROR		1
#define LUMOS_LOG_LEVEL_WARNING		2
#define LUMOS_LOG_LEVEL_INFO		3

#ifdef MOUSE_MOVED
#undef MOUSE_MOVED
#endif

namespace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)");
	}
}

namespace lumos {

	namespace core {

		static char to_string_buffer[1024 * 10];
		static char sprintf_buffer[1024 * 10];

		LS_API void PlatformLogMessage(uint level, const char* message);

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

		template <typename T>
		static const char* to_string(const T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <>
		static const char* to_string<char>(const char& t)
		{
			return &t;
		}

		template <>
		static const char* to_string<char*>(char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t)
		{
			return (const char*)t;
		}

		template <>
		static const char* to_string<wchar_t*>(wchar_t* const& t)
		{
			wcstombs(sprintf_buffer, t, 1024 * 10);
			return sprintf_buffer;
		}

		template <>
		static const char* to_string<const wchar_t*>(const wchar_t* const& t)
		{
			wcstombs(sprintf_buffer, t, 1024 * 10);
			return sprintf_buffer;
		}

		template <>
		static const char* to_string<const char*>(const char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<String>(const String& t)
		{
			return t.c_str();
		}

		template <>
		static const char* to_string<bool>(const bool& t)
		{
			return t ? "true" : "false";
		}

		template <typename T>
		static String format_iterators(T& begin, T& end)
		{
			String result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = StringFormat::ToString(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template<typename X, typename Y>
		static const char* to_string(const std::pair<typename X, typename Y>& v)
		{
			sprintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, int32& position, First&& first)
		{
			const char* formatted = lumos::core::to_string<First>(first);
			int32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int32& position, First&& first, Args&&... args)
		{
			const char* formatted = lumos::core::to_string<First>(first);
			int32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
				print_log_internal(buffer, position, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log_message(int32 level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			int32 position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline)
				buffer[position++] = '\n';

			buffer[position] = 0;

			PlatformLogMessage(level, buffer);
		}

	}

}

#ifndef LUMOS_LOG_LEVEL
#define LUMOS_LOG_LEVEL LUMOS_LOG_LEVEL_INFO
#endif

#if LUMOS_LOG_LEVEL >= LUMOS_LOG_LEVEL_FATAL
#define LS_FATAL(...) lumos::core::log_message(LUMOS_LOG_LEVEL_FATAL, true, "LUMOS:    ", __VA_ARGS__)
#define _LS_FATAL(...) lumos::core::log_message(LUMOS_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define LS_FATAL(...)
#define _LS_FATAL(...)
#endif

#if LUMOS_LOG_LEVEL >= LUMOS_LOG_LEVEL_ERROR
#define LS_ERROR(...) lumos::core::log_message(LUMOS_LOG_LEVEL_ERROR, true, "LUMOS:    ", __VA_ARGS__)
#define _LS_ERROR(...) lumos::core::log_message(LUMOS_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define LS_ERROR(...)
#define _LS_ERROR(...)
#endif

#if LUMOS_LOG_LEVEL >= LUMOS_LOG_LEVEL_WARNING
#define LS_WARNING(...) lumos::core::log_message(LUMOS_LOG_LEVEL_WARNING, true, "LUMOS:    ", __VA_ARGS__)
#define _LS_WARNING(...) lumos::core::log_message(LUMOS_LOG_LEVEL_WARNING, false, __VA_ARGS__)
#else
#define LS_WARNING(...)
#define _LS_WARNING(...)
#endif

#if LUMOS_LOG_LEVEL >= LUMOS_LOG_LEVEL_INFO
#define LS_INFO(...) lumos::core::log_message(LUMOS_LOG_LEVEL_INFO, true, "LUMOS:    ", __VA_ARGS__)
#define _LS_INFO(...) lumos::core::log_message(LUMOS_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define LS_INFO(...)
#define _LS_INFO(...)
#endif

#ifdef LS_DEBUG
#define LS_ASSERT(x, ...) \
		if (!(x)) {\
			LS_FATAL("*************************"); \
			LS_FATAL("    ASSERTION FAILED!    "); \
			LS_FATAL("*************************"); \
			LS_FATAL(__FILE__, ": ", __LINE__); \
			LS_FATAL("Condition: ", #x); \
			LS_FATAL(__VA_ARGS__); \
			__debugbreak(); \
		}
#else
#define LS_ASSERT(x, ...)
#endif