#pragma once

#ifndef __RESPONSE_HPP__
#define __RESPONSE_HPP__

#include "Config.hpp"

#include "Types.hpp"
#include "ErrorCode.hpp"

struct DllExport Response
{
	ErrorCode errorCode;
	Pointer data;

	Response();
	Response(ErrorCode errorCode, Pointer data = null);
};

#endif // __RESPONSE_HPP__
