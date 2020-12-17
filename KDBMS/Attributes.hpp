#pragma once

#ifndef __ATTRIBUTES_HPP__
#define __ATTRIBUTES_HPP__

#include "Config.hpp"

#include "Printable.hpp"

struct DllExport Attributes : Printable
{
	bool nonNull : 1;
	bool primaryKey : 1;
	bool foreignKey : 1;

	Attributes(bool nonNull = false, bool primaryKey = false, bool foreignKey = false);

	String ToString() override;
};

#endif // __ATTRIBUTES_HPP__
