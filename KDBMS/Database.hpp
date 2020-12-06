#pragma once

#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include "Config.h"

#include <list>
#include <vector>
#include <string>

#include "Types.h"

using namespace std;

enum struct DllExport ErrorCode
{
	OK,
	NOT_IMPLEMENTED,
	NOT_FOUND,
	NULL_ARGUMENT,
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

enum struct DllExport Type : uint32_t
{
	NONE = 0u << 0,
	BOOL = 1u << 0,
	BYTE = 1u << 1,
	CHAR = 1u << 2,
	SHORT = 1u << 3,
	USHORT = 1u << 4,
	INT = 1u << 5,
	UINT = 1u << 6,
	LONG = 1u << 7,
	ULONG = 1u << 8,
	FLOAT = 1u << 9,
	DOUBLE = 1u << 10,
	STRING = 1u << 11,
	ENUM = 1u << 12,
	DATE = 1u << 13,
	TIME = 1u << 14,
	DATETIME = 1u << 15,
	BLOB = 1u << 16,
	ARRAY = 1u << 31
};

struct DllExport Enum
{
	String value;
	list<String> values;
};

struct DllExport Date
{
	// TODO
};

struct DllExport Time
{
	// TODO
};

struct DllExport DateTime
{
	Date date;
	Time time;
};

typedef vector<char> Blob;

union DllExport Data
{
	Pointer pointer;
	uint64_t value;
	float singlePrecisionFloating;
	double doublePrecisionFloating;

	Data(Type type, Pointer data)
	{
		if ((uint32_t)type | (uint32_t)Type::ARRAY)
		{
			pointer = data;
		}
		else
		{
			switch (type)
			{
			case Type::BOOL:
				value = *(bool *)data;
				break;
			case Type::CHAR:
				value = *(char *)data;
				break;
			case Type::SHORT:
				value = *(signed short int *)data;
				break;
			case Type::USHORT:
				value = *(unsigned short int *)data;
				break;
			case Type::INT:
				value = *(signed long int *)data;
				break;
			case Type::UINT:
				value = *(unsigned long int *)data;
				break;
			case Type::LONG:
				value = *(signed long long int *)data;
				break;
			case Type::ULONG:
				value = *(long unsigned long int *)data;
				break;
			case Type::FLOAT:
				singlePrecisionFloating = *(float *)data;
				break;
			case Type::DOUBLE:
				doublePrecisionFloating = *(double *)data;
				break;
			case Type::STRING:
				pointer = (String *)data;
				break;
			case Type::ENUM:
				pointer = (Enum *)data;
				break;
			case Type::DATE:
				pointer = (Date *)data;
				break;
			case Type::TIME:
				pointer = (Time *)data;
				break;
			case Type::DATETIME:
				pointer = (DateTime *)data;
				break;
			case Type::BLOB:
				pointer = (Blob *)data;
				break;
			default:
				value = 0;
				break;
			}
		}
	}
};

enum struct DllExport ObjectType
{
	NONE,
	DATABASE,
	TABLE,
	COLUMN,
	ROW,
	PRIMITIVE
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
	Pointer data;

	SerializedObject();
	SerializedObject(ObjectType type, uint64_t length, Pointer data);
	SerializedObject(Type primitiveType, uint64_t length, Pointer data);
};

struct DllExport Serializeable
{
	virtual SerializedObject Serialize() = 0;
	virtual bool Deserialize(char *rows) = 0;
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
	bool Deserialize(char *rows) override;
};

struct DllExport TableRow : Serializeable
{
	vector<Data> fields;

	TableRow(vector<Data> fields);

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;
};

struct DllExport Table : Serializeable
{
	String name;
	vector<TableColumn> *columns;
	list<TableRow> rows;

	Table(String name, vector<TableColumn> *columns = nullptr);

	Response Insert(vector<Data> *row);
	Response Select();
	Response Update();
	Response Delete();

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;
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

	SerializedObject Serialize() override;
	bool Deserialize(char *rows) override;

private:
	list<Table *> *tables;

	Table *FindTableByName(String name);
	bool DeleteTable(Table *table);
};

#endif // __DATABASE_HPP__
