#pragma once

#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include "Config.hpp"

#include <list>
#include <vector>
#include <string>

#include "Types.hpp"
#include "Table.hpp"
#include "Serializeable.hpp"
#include "SerializedObject.hpp"
#include "Response.hpp"
#include "IO.hpp"

using namespace std;

struct DllExport Database : Serializeable, Printable
{
	String name;

	Database(String name, list<Table *> *tables = nullptr);

	Response CreateTable(String name, vector<TableColumn> *columns = nullptr);
	Response AlterTable(String name, vector<TableColumn> *columns = nullptr);
	Response DropTable(String name);
	Response FindTable(String name);
	Response SaveToFile(String fileName);
	Response LoadFromFile(String fileName);

	SerializedObject Serialize() override;
	bool Deserialize(SerializedObject object) override;
	String ToString() override;

private:
	list<Table *> *tables;

	Table *FindTableByName(String name);
	bool DeleteTable(Table *table);
};

#endif // __DATABASE_HPP__
