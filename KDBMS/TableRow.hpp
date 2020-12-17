#pragma once

#ifndef __TABLEROW_HPP__
#define __TABLEROW_HPP__

#include "Config.hpp"

#include <vector>

#include "Types.hpp"
#include "TableColumn.hpp"
#include "Serializeable.hpp"
#include "Printable.hpp"
#include "Data.hpp"

using namespace std;

struct DllExport TableRow : Serializeable, Printable
{
	vector<TableColumn> *columns;
	vector<Data> fields;

	TableRow(vector<TableColumn> *columns, vector<Data> fields);

	SerializedObject Serialize() override;
	bool Deserialize(SerializedObject object) override;
	String ToString() override;
};

#endif // __TABLEROW_HPP__
