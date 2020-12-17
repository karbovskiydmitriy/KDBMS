#pragma once

#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include "Config.hpp"

#include <list>
#include <vector>
#include <string>

#include "Types.hpp"
#include "Serializeable.hpp"
#include "Printable.hpp"
#include "SerializedObject.hpp"
#include "Response.hpp"
#include "Condition.hpp"
#include "Attributes.hpp"
#include "TableColumn.hpp"
#include "TableRow.hpp"

using namespace std;

struct Response;
struct Condition;

struct DllExport Table : Serializeable, Printable
{
	String name;
	vector<TableColumn> *columns;
	list<TableRow *> rows;

	Table(String name, vector<TableColumn> *columns);

	Response Insert(TableRow *row);
	Response Select(Condition *condition = nullptr);
	Response Update(Condition *condition, String columnName, Data value);
	Response Update(Condition *condition, int index, Data value);
	Response Delete(Condition *condition);
	int GetColumnIndex(String columnName);
	Type GetColumnType(String columnName);

	SerializedObject Serialize() override;
	bool Deserialize(SerializedObject object) override;
	String ToString() override;

private:
	bool DeleteRow(TableRow *row);
};

#endif // __TABLE_HPP__
