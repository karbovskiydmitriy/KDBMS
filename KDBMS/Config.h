#pragma once

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

typedef unsigned char byte;

#define DllExport __declspec(dllexport)

#ifndef UNICODE
#	define String string
#	define print printf
#else
#	define String wstring
#	define print wprintf
#endif

// typedef TCHAR *String;

#pragma warning(disable: 4251)

#endif // __CONFIG_H__
