#pragma once

#ifndef __SERIALIZEDOBJECT_HPP__
#define __SERIALIZEDOBJECT_HPP__

#include "Config.hpp"

#include "Types.hpp"

struct DllExport SerializedObject
{
	ObjectType type;
	Type primitiveType;
	uint64_t length;
	Pointer data;

	SerializedObject();
	SerializedObject(ObjectType type, uint64_t length, Pointer data);
	SerializedObject(Type primitiveType, uint64_t length, Pointer data);
	~SerializedObject();
};

#endif // __SERIALIZEDOBJECT_HPP__
