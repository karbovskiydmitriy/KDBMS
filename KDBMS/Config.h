#pragma once

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

#define DllExport __declspec(dllexport)

#ifndef UNICODE
#	define String string
#	define To_String to_string
#	define TEXT(s) (s)
#	define print printf
#else
#	define String wstring
#	define To_String to_wstring
#	define TEXT(s) (L##s)
#	define print wprintf
#endif // UNICODE

#pragma warning(disable: 4251)

#endif // __CONFIG_H__
