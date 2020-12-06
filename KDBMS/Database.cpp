#include "Database.hpp"

Data::Data(Type type, Pointer data)
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

Attributes::Attributes(bool nonNull, bool primaryKey, bool foreignKey)
{
	this->nonNull = nonNull;
	this->primaryKey = primaryKey;
	this->foreignKey = foreignKey;
}

TableColumn::TableColumn(String name, Type type, Attributes attributes)
{
	this->name = name;
	this->type = type;
	this->attributes = attributes;
}

Database::Database(String name, list<Table *> *tables)
{
	this->name = name;

	if (tables != nullptr)
	{
		this->tables = tables;
	}
	else
	{
		this->tables = new list<Table *>();
	}
}

Response Database::CreateTable(String name, vector<TableColumn> *columns)
{
	Table *table = new Table(name, columns);
	this->tables->push_back(table);

	return Response(ErrorCode::OK, table);
}

Response Database::AlterTable(String name, vector<TableColumn> *columns)
{
	Table *table = FindTableByName(name);
	table->columns = columns;

	return Response(ErrorCode::OK, table);
}

Response Database::DropTable(String name)
{
	Table *table = FindTableByName(name);

	if (table != nullptr)
	{
		if (DeleteTable(table))
		{
			return Response(ErrorCode::OK);
		}
	}

	return Response(ErrorCode::NOT_FOUND);
}

SerializedObject Database::Serialize()
{
	return SerializedObject();
}

bool Database::Deserialize(char *rows)
{
	return false;
}

Table *Database::FindTableByName(String name)
{
	for (const auto &iterator : *this->tables)
	{
		if (iterator->name == name)
		{
			return iterator;
		}
	}

	return nullptr;
}

bool Database::DeleteTable(Table *table)
{
	for (const auto &iterator : *this->tables)
	{
		if (iterator == table)
		{
			this->tables->remove(table);
			delete table;

			return true;
		}
	}

	return false;
}

String Table::ToString()
{
	return String();
}
