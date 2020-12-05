#pragma once

#ifndef __SQL_HPP__
#define __SQL_HPP__

#include "Config.h"

#include <list>
#include <vector>
#include <string>
#include "Types.h"

using namespace std;

#ifdef x86

typedef union
{
	Pointer pointer;
	uint32_t value;
} SQLData;

#else

typedef union
{
	Pointer pointer;
	uint64_t value;
} SQLData;

#endif

enum class ErrorCode
{
	NAME_CONFLICT,
	TYPE_CONFLICT
};

enum SQLType
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
};

enum Type
{
	_NONE,
	_BOOL,
	_BYTE,
	_CHAR,
	_SHORT,
	_USHORT,
	_INT,
	_UINT,
	_LONG,
	_ULONG,
	_FLOAT,
	_DOUBLE,
	_DECIMAL,
	_STRING,
	_ENUM,
	_DATE,
	_TIME,
	_DATETIME
};

enum ObjectType
{
	NONE,
	DATABASE,
	TABLE,
	COLUMN,
	ROW
};

struct SerializedObject
{
	ObjectType type;
	Type primitiveType;
	uint64_t length;
	Pointer object;
};

struct SQLAttributes
{
	bool nonNull : 1;
	bool primaryKey : 1;
	bool foreignKey : 1;
};

struct TableColumn
{
	String name;
	/*SQL*/Type type;
	
	
};

struct SQLResponse
{
	// SQLRequest *request;
	// vector<SQLColumn> data;
	Pointer data;
	ErrorCode errorCode;
};

struct TableRow
{

};

struct Table
{
	list<TableColumn> columns;
	string name;
};

struct Database
{
	vector<Table> tables;

	SQLResponse CreateTable(String name, vector<TableColumn> *columns = nullptr);
	SQLResponse AlterTable(String name, TableColumn column);
	SQLResponse AlterTable_Modify(String name, TableColumn column);
	SQLResponse AlterTable_DropColumn(String name);
	SQLResponse AlterTable_RenameTo(String name, String newName);
	SQLResponse AlterTable_Enable(String name, String attribute);
	SQLResponse AlterTable_Disable(String name, String attribute);
	SQLResponse DropTable(String name);
	SQLResponse Insert();
	SQLResponse Select();
	SQLResponse Update();
	SQLResponse Delete();
};

#endif // __SQL_HPP__
