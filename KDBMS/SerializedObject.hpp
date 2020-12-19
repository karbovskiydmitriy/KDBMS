#pragma once

#ifndef __SERIALIZEDOBJECT_HPP__
#define __SERIALIZEDOBJECT_HPP__

#include "Config.hpp"

#include "Types.hpp"

#pragma pack(push, 1)

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

#pragma pack(pop)

#endif // __SERIALIZEDOBJECT_HPP__
