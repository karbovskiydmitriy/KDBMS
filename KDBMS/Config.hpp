#pragma once

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>

#define DllExport __declspec(dllexport)

#ifndef UNICODE
#	define String string
#	define To_String to_string
#	define Strlen strlen
#	define TEXT(s) (s)
#	define print printf
#else
#	define String wstring
#	define To_String to_wstring
#	define Strlen wstrlen
#	define TEXT(s) (L##s)
#	define print wprintf
#endif // UNICODE

#pragma warning(disable: 4251)

#endif // __CONFIG_HPP__
