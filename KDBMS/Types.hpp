#pragma once

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include "Config.h"

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

#endif // __TYPES_HPP__
