#pragma once

#ifndef __PRINTABLE_HPP__
#define __PRINTABLE_HPP__

#include "Config.hpp"

#include <string>

using namespace std;

struct DllExport Printable
{
	virtual String ToString() = 0;
};

#endif // __PRINTABLE_HPP__
