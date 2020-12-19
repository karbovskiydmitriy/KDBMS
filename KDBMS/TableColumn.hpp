#pragma once

#ifndef __TABLECOLUMN_HPP__
#define __TABLECOLUMN_HPP__

#include "Config.hpp"

#include <string>

#include "Serializeable.hpp"
#include "Types.hpp"
#include "Attributes.hpp"

using namespace std;

struct DllExport TableColumn : Serializeable
{
	String name;
	Type type;
	Attributes attributes;

	TableColumn();
	TableColumn(String name, Type type, Attributes attributes = 0);

	SerializedObject Serialize() override;
	bool Deserialize(SerializedObject object) override;
};

#endif // __TABLECOLUMN_HPP__
