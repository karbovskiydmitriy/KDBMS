#pragma once

#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "Config.h"

#include <vector>

#include "Data.hpp"
#include "Types.hpp"

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

struct DllExport Response
{
	ErrorCode errorCode;
	Pointer data;

	Response();
	Response(ErrorCode errorCode, Pointer data = null);
};

enum struct DllExport Comparison
{
	EQUALS,
	NOT_EQUALS,
	LESS_THEN,
	LESS_OR_EQUALS_THEN,
	GREATER_THAN,
	GREATER_OR_EQUALS_THAN
};

struct DllExport Condition
{
	String column;
	Data value;
	Type type;
	Comparison comparison;
	Condition *andCondition;
	Condition *orCondition;

	Condition(String column, Data value, Type type, Comparison comparison, Condition *andCondition = nullptr, Condition *orCondition = nullptr);
	
	bool Check(Data value);
};

#endif // __QUERY_HPP__
