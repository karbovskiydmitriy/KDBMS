#include "Database.hpp"

Response::Response()
{
	this->errorCode = ErrorCode::OK;
	this->data = null;
}

Response::Response(ErrorCode errorCode, Pointer data)
{
	this->errorCode = errorCode;
	this->data = data;
}

SerializedObject::SerializedObject()
{
	this->type = ObjectType::NONE;
	this->primitiveType = Type::NONE;
	this->length = 0;
	this->data = null;
}

SerializedObject::SerializedObject(ObjectType type, uint64_t length, Pointer data)
{
	this->type = type;
	this->primitiveType = Type::NONE;
	this->length = length;
	this->data = data;
}

SerializedObject::SerializedObject(Type primitiveType, uint64_t length, Pointer data)
{
	this->type = ObjectType::PRIMITIVE;
	this->primitiveType = primitiveType;
	this->length = length;
	this->data = data;
}

Attributes::Attributes()
{
	this->nonNull = 0;
	this->primaryKey = 0;
	this->foreignKey = 0;
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

bool TableColumn::Deserialize(char *rows)
{
	return false;
}

TableRow::TableRow(vector<Data> fields)
{
	this->fields = fields;
}

SerializedObject TableRow::Serialize()
{
	return SerializedObject();
}

bool TableRow::Deserialize(char *rows)
{
	return false;
}

Table::Table(String name, vector<TableColumn> *columns)
{
	this->name = name;
	this->columns = columns;
	// this->rows.resize(128);
}

Response Table::Insert(vector<Data> *row)
{
	if (row != nullptr)
	{
		return Response(ErrorCode::NOT_IMPLEMENTED);
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

Response Table::Select()
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Table::Update()
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Table::Delete()
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

SerializedObject Table::Serialize()
{
	return SerializedObject();
}

bool Table::Deserialize(char *rows)
{
	return false;
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
