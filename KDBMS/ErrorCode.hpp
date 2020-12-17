#pragma once

#ifndef __ERRORCODE_HPP__
#define __ERRORCODE_HPP__

#include "Config.hpp"

enum struct DllExport ErrorCode
{
	OK = 0,
	NOT_IMPLEMENTED,
	NOT_FOUND,
	NULL_ARGUMENT,
	NAME_CONFLICT,
	TYPE_CONFLICT,
	CONDITION_ERROR
};

#endif // __ERRORCODE_HPP__
