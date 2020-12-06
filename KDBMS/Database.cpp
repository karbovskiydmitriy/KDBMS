#include "Database.hpp"

Response::Response()
{
	errorCode = ErrorCode::OK;
	data = null;
}

Response::Response(ErrorCode errorCode, Pointer data)
{
	this->errorCode = errorCode;
	this->data = data;
}

SerializedObject::SerializedObject()
{
	type = ObjectType::NONE;
	primitiveType = Type::NONE;
	length = 0;
	object = null;
}

Attributes::Attributes()
{
	nonNull = 0;
	primaryKey = 0;
	foreignKey = 0;
}

TableColumn::TableColumn(String name, Type type, Attributes attributes)
{
	this->name = name;
	this->type = type;
	this->attributes = attributes;
}

SerializedObject TableColumn::Serialize()
{
	return SerializedObject();
}

bool TableColumn::Deserialize(char *data)
{
	return false;
}

SerializedObject TableRow::Serialize()
{
	return SerializedObject();
}

bool TableRow::Deserialize(char *data)
{
	return false;
}

Table::Table(String name, vector<TableColumn> *columns)
{
	this->name = name;
	this->columns = columns;
}

SerializedObject Table::Serialize()
{
	return SerializedObject();
}

bool Table::Deserialize(char *data)
{
	return false;
}

Database::Database(String name, list<Table *> *tables)
{
	this->name = name;
	if (tables != nullptr)
	{
		this->tables = *tables;
	}
}

Response Database::CreateTable(String name, vector<TableColumn> *columns)
{
	Table *table = new Table(name, columns);

	return Response(ErrorCode::OK, table);
}

Response Database::AlterTable(String name, vector<TableColumn> *columns)
{
	// Table *table = nullptr;// = new Table(name, columns);
	Table *table = FindTableByName(name);
	table->columns = columns;

	return Response(ErrorCode::OK, table);
}

/*Response Database::AlterTable_Modify(String name, TableColumn column)
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Database::AlterTable_DropColumn(String name)
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Database::AlterTable_RenameTo(String name, String newName)
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Database::AlterTable_Enable(String name, String attribute)
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Database::AlterTable_Disable(String name, String attribute)
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}*/

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

Response Database::Insert()
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Database::Select()
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Database::Update()
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Database::Delete()
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

SerializedObject Database::Serialize()
{
	return SerializedObject();
}

bool Database::Deserialize(char *data)
{
	return false;
}

Table *Database::FindTableByName(String name)
{
	for (const auto &iterator : tables)
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
	for (const auto &iterator : tables)
	{
		if (iterator == table)
		{
			tables.remove(table);
			delete table;

			return true;
		}
	}

	return false;
}
