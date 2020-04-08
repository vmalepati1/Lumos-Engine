#pragma once

#pragma warning (disable:4251)

#ifdef LS_PLATFORM_WINDOWS
#ifdef LS_EXPORT_DLL
#define LS_API __declspec(dllexport)
#else
#define LS_API __declspec(dllimport)
#endif
#else
#define LS_API
#endif

#define BIT(x) (1 << x)
#define SAFE_DELETE(a) if( (a) != NULL ) { lsdel (a); (a) = NULL; }
#define METHOD_1(x) std::bind(x, this, std::placeholders::_1)
#define METHOD(x) METHOD_1(x)