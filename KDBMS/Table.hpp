#pragma once

#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include "Config.h"

#include <list>
#include <vector>
#include <string>

#include "Types.hpp"
#include "Interfaces.hpp"
#include "Serialization.hpp"
#include "Query.hpp"
#include "Data.hpp"

using namespace std;

struct DllExport Attributes
{
	bool nonNull : 1;
	bool primaryKey : 1;
	bool foreignKey : 1;

	Attributes(bool nonNull = false, bool primaryKey = false, bool foreignKey = false);
};

struct DllExport TableColumn : Serializeable
{
	String name;
	Type type;
	Attributes attributes;

	TableColumn(String name, Type type, Attributes attributes = 0);

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;
};

struct DllExport TableRow : Serializeable, Printable
{
	vector<TableColumn> *columns;
	vector<Data> fields;

	TableRow(vector<TableColumn> *columns, vector<Data> fields);

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;
	String ToString() override;
};

struct DllExport Table : Serializeable, Printable
{
	String name;
	vector<TableColumn> *columns;
	list<TableRow *> rows;

	Table(String name, vector<TableColumn> *columns = nullptr);

	Response Insert(TableRow *row);
	Response Select(Condition *condition);
	Response Update(); // TODO
	Response Delete(Condition *condition);

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;
	String ToString() override;

private:
	bool DeleteRow(TableRow *row);
};

#endif // __TABLE_HPP__
