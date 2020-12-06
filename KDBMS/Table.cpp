#include "Table.hpp"

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
}

Response Table::Insert(TableRow *row)
{
	if (row != nullptr)
	{
		this->rows.push_back(row);

		return Response(ErrorCode::OK);
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

Response Table::Select(Condition *condition)
{
	if (condition != nullptr)
	{
		vector<TableRow *> *entries = new vector<TableRow *>();

		for (const auto &iterator : this->rows)
		{
			// TODO

			if (true)
			{
				entries->push_back(iterator);
			}
		}

		return Response(ErrorCode::OK, entries);
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

Response Table::Update() // TODO
{
	return Response(ErrorCode::NOT_IMPLEMENTED);
}

Response Table::Delete(Condition *condition)
{
	if (condition != nullptr)
	{
		for (const auto &iterator : this->rows)
		{
			// TODO
		}

		return Response(ErrorCode::NOT_IMPLEMENTED);
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

SerializedObject Table::Serialize()
{
	return SerializedObject();
}

bool Table::Deserialize(char *rows)
{
	return false;
}

bool Table::DeleteRow(TableRow *row)
{
	if (row != nullptr)
	{
		for (const auto &iterator : this->rows)
		{
			if (iterator == row)
			{
				this->rows.remove(row);

				return true;
			}
		}
	}

	return false;
}
