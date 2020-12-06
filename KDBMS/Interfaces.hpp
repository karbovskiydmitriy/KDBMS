#pragma once

#ifndef __INTERFACES_HPP__
#define __INTERFACES_HPP__

#include "Config.h"

#include <String>

#include "Serialization.hpp"

using namespace std;

struct DllExport Serializeable
{
	virtual SerializedObject Serialize() = 0;
	virtual bool Deserialize(char *rows) = 0;
};

struct DllExport Printable
{
	virtual String ToString() = 0;
};

#endif // __INTERFACES_HPP__
