#include "Database.hpp"

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
