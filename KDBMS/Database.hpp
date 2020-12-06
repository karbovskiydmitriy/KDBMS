#pragma once

#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include "Config.h"

#include <list>
#include <vector>
#include <string>

#include "Types.h"

using namespace std;

#ifdef x86

union DllExport Data
{
	Pointer pointer;
	uint32_t value;
};

#else

union DllExport Data
{
	Pointer pointer;
	uint64_t value;
};

#endif

enum struct DllExport ErrorCode
{
	OK,
	NOT_IMPLEMENTED,
	NOT_FOUND,
	NAME_CONFLICT,
	TYPE_CONFLICT
};

/*enum struct SQLType
{
	UNKNOWN = 0,
	// string types
	CHAR = 1,
	VARCHAR,
	BINARY,
	VARBINARY,
	TINYBLOB,
	TINYTEXT,
	TEXT,
	BLOB,
	MEDIUMTEXT,
	MEDIUMBLOB,
	LONGTEXT,
	LONGBLOB,
	ENUM,
	SET,
	// numeric types
	BIT,
	TINYINT,
	BOOL,
	SMALLINT,
	MEDIUMINT,
	INT,
	BIGINT,
	FLOAT,
	DOUBLE,
	DECIMAL,
	// date and time types
	DATE,
	DATETIME,
	TIMESTAMP,
	TIME,
	YEAR
};*/

enum struct DllExport Type
{
	NONE = 0,
	BOOL,
	BYTE,
	CHAR,
	SHORT,
	USHORT,
	INT,
	UINT,
	LONG,
	ULONG,
	FLOAT,
	DOUBLE,
	DECIMAL,
	STRING,
	ENUM,
	DATE,
	TIME,
	DATETIME,
	ARRAY = -1
};

enum struct DllExport ObjectType
{
	NONE,
	DATABASE,
	TABLE,
	COLUMN,
	ROW
};

struct DllExport Response
{
	ErrorCode errorCode;
	Pointer data;

	Response();
	Response(ErrorCode errorCode, Pointer data = null);
};

struct DllExport SerializedObject
{
	ObjectType type;
	Type primitiveType;
	uint64_t length;
	Pointer object;

	SerializedObject();
};

struct DllExport Serializeable
{
	virtual SerializedObject Serialize() = 0;
	virtual bool Deserialize(char *data) = 0;
};

struct DllExport Attributes
{
	bool nonNull : 1;
	bool primaryKey : 1;
	bool foreignKey : 1;

	Attributes();
};

struct DllExport TableColumn : Serializeable
{
	String name;
	Type type;
	Attributes attributes;

	TableColumn(String name, Type type, Attributes attributes);

	SerializedObject Serialize() override;
	bool Deserialize(char *data) override;
};

struct DllExport TableRow : Serializeable
{
	vector<Data> fields;

	SerializedObject Serialize() override;
	bool Deserialize(char *data) override;
};

struct DllExport Table : Serializeable
{
	String name;
	vector<TableColumn> *columns;

	Table(String name, vector<TableColumn> *columns = nullptr);

	SerializedObject Serialize() override;
	bool Deserialize(char *data) override;
};

struct DllExport Database : Serializeable
{
	String name;

	Database(String name, list<Table *> *tables = nullptr);

	Response CreateTable(String name, vector<TableColumn> *columns = nullptr);
	Response AlterTable(String name, vector<TableColumn> *columns = nullptr);
	/*Response AlterTable_Modify(String name, TableColumn column);
	Response AlterTable_DropColumn(String name);
	Response AlterTable_RenameTo(String name, String newName);
	Response AlterTable_Enable(String name, String attribute);
	Response AlterTable_Disable(String name, String attribute);*/
	Response DropTable(String name);
	Response Insert();
	Response Select();
	Response Update();
	Response Delete();

	SerializedObject Serialize() override;
	bool Deserialize(char *data) override;

private:
	list<Table *> tables;

	Table *FindTableByName(String name);
	bool DeleteTable(Table *table);
};

#endif // __DATABASE_HPP__
