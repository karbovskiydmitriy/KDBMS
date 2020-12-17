#pragma once

#ifndef __SERIALIZEABLE_HPP__
#define __SERIALIZEABLE_HPP__

#include "Config.hpp"

#include "SerializedObject.hpp"

struct DllExport Serializeable
{
	virtual SerializedObject Serialize() = 0;
	virtual bool Deserialize(SerializedObject object) = 0;
};

#endif // __SERIALIZEABLE_HPP__
