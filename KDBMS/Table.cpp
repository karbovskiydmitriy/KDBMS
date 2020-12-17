#include "Table.hpp"

Table::Table(String name, vector<TableColumn> *columns)
{
	this->name = name;
	this->columns = columns;
}

Response Table::Insert(TableRow *row)
{
	if (row != nullptr)
	{
		if (row->fields.size() == this->columns->size())
		{
			this->rows.push_back(row);

			return Response(ErrorCode::OK);
		}
		else
		{
			return Response(ErrorCode::TYPE_CONFLICT);
		}
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
			if (condition->Check(iterator->fields))
			{
				entries->push_back(iterator);
			}
		}

		return Response(ErrorCode::OK, entries);
	}
	else
	{
		vector<TableRow *> *entries = new vector<TableRow *>();

		for (const auto &iterator : this->rows)
		{
			entries->push_back(iterator);
		}

		return Response(ErrorCode::OK, entries);
	}
}

Response Table::Update(Condition *condition, String columnName, Data value)
{
	if (condition != nullptr)
	{
		int index = this->GetColumnIndex(columnName);
		if (index != -1)
		{
			for (const auto &iterator : this->rows)
			{
				if (condition->Check(iterator->fields))
				{
					iterator->fields.data()[index] = value;
				}
			}
		}
		else
		{
			return Response(ErrorCode::NOT_FOUND);
		}

		return Response(ErrorCode::OK);
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

Response Table::Update(Condition *condition, int index, Data value)
{
	if (condition != nullptr)
	{
		if (index >= 0 && index < (int)this->columns->size())
		{
			for (const auto &iterator : this->rows)
			{
				if (condition->Check(iterator->fields))
				{
					iterator->fields.data()[index] = value;
				}
			}
		}
		else
		{
			return Response(ErrorCode::NOT_FOUND);
		}

		return Response(ErrorCode::OK);
	}

	return Response(ErrorCode::NULL_ARGUMENT);
}

Response Table::Delete(Condition *condition)
{
	if (condition != nullptr)
	{
		for (const auto &iterator : this->rows)
		{
			if (condition->Check(iterator->fields))
			{
				DeleteRow(iterator);
			}
		}

		return Response(ErrorCode::OK);
	}
	else
	{
		this->rows.clear();

		return Response(ErrorCode::OK);
	}
}

int Table::GetColumnIndex(String columnName)
{
	if (this->columns != nullptr)
	{
		for (int i = 0; i < (int)this->columns->size(); i++)
		{
			if (this->columns->data()[i].name == columnName)
			{
				return i;
			}
		}

		return -1;
	}
	else
	{
		return -1;
	}
}

Type Table::GetColumnType(String columnName)
{
	if (this->columns != nullptr)
	{
		for (int i = 0; i < (int)this->columns->size(); i++)
		{
			if (this->columns->data()[i].name == columnName)
			{
				return this->columns->data()->type;
			}
		}

		return Type::NONE;
	}
	else
	{
		return Type::NONE;
	}
}

SerializedObject Table::Serialize()
{
	return SerializedObject();
}

bool Table::Deserialize(SerializedObject object)
{
	return false;
}

String Table::ToString()
{
	String result = String(TEXT("Table\n")) + String(TEXT("Columns: "));

	for (const auto &iterator : *this->columns)
	{
		result += "\t" + iterator.name;
	}

	return result;
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
