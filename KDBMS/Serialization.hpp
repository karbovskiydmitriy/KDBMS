#pragma once

#ifndef __SERIALIZATION_HPP__
#define __SERIALIZATION_HPP__

#include "Config.h"

#include "Types.hpp"

enum struct DllExport ObjectType
{
	NONE,
	DATABASE,
	TABLE,
	COLUMN,
	ROW,
	PRIMITIVE
};

struct DllExport SerializedObject
{
	ObjectType type;
	Type primitiveType;
	uint64_t length;
	Pointer data;

	SerializedObject();
	SerializedObject(ObjectType type, uint64_t length, Pointer data);
	SerializedObject(Type primitiveType, uint64_t length, Pointer data);
};

#endif // __SERIALIZATION_HPP__
