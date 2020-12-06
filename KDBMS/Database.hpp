#pragma once

#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include "Config.h"

#include <list>
#include <vector>
#include <string>

#include "Types.hpp"
#include "Table.hpp"
#include "Interfaces.hpp"
#include "Serialization.hpp"
#include "Query.hpp"

using namespace std;

enum struct DllExport ErrorCode;
enum struct DllExport ObjectType;
struct DllExport Response;
struct DllExport Condition;
struct DllExport Database;

struct DllExport Database : Serializeable
{
	String name;

	Database(String name, list<Table *> *tables = nullptr);

	Response CreateTable(String name, vector<TableColumn> *columns = nullptr);
	Response AlterTable(String name, vector<TableColumn> *columns = nullptr);
	Response DropTable(String name);

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;

private:
	list<Table *> *tables;

	Table *FindTableByName(String name);
	bool DeleteTable(Table *table);
};

#endif // __DATABASE_HPP__
