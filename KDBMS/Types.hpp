#pragma once

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include "Config.hpp"

typedef void *Pointer;

constexpr Pointer null = (Pointer)0;

// typedef unsigned char byte;

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
	CHAR = 1u << 1,
	BYTE = 1u << 2,
	UBYTE = 1u << 3,
	SHORT = 1u << 4,
	USHORT = 1u << 5,
	INT = 1u << 6,
	UINT = 1u << 7,
	LONG = 1u << 8,
	ULONG = 1u << 9,
	FLOAT = 1u << 10,
	DOUBLE = 1u << 11,
	STRING = 1u << 12,
	ENUM = 1u << 13,
	DATE = 1u << 14,
	TIME = 1u << 15,
	DATETIME = 1u << 16,
	BLOB = 1u << 17,
	ARRAY = 1u << 31
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

#endif // __TYPES_HPP__
