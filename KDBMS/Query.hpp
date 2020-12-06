#pragma once

#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "Config.h"

#include "Types.hpp"

enum struct DllExport ErrorCode
{
	OK,
	NOT_IMPLEMENTED,
	NOT_FOUND,
	NULL_ARGUMENT,
	NAME_CONFLICT,
	TYPE_CONFLICT
};

struct DllExport Response
{
	ErrorCode errorCode;
	Pointer data;

	Response();
	Response(ErrorCode errorCode, Pointer data = null);
};

struct DllExport Condition
{
	// TODO
};

#endif // __QUERY_HPP__
