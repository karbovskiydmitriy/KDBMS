#pragma once

#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef unsigned char byte;

#ifndef UNICODE
#	define String string
#	define TEXT(s) (s)
#else
#	define String wstring
#	define TEXT(s) (L#s)
#endif

#endif // __CONFIG_H__
