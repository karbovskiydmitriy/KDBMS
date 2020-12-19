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
	uint32_t nameLength = Strlen(this->name.c_str());
	uint64_t length = 12ull + nameLength;

	vector<SerializedObject> serializedColumns;
	for (auto column = this->columns->begin(); column != this->columns->end(); column++)
	{
		SerializedObject object = column->Serialize();
		serializedColumns.push_back(object);
		length += offsetof(SerializedObject, data) + object.length;
	}

	vector<SerializedObject> serializedRows;
	for (const auto &row : this->rows)
	{
		SerializedObject object = row->Serialize();
		serializedRows.push_back(object);
		length += offsetof(SerializedObject, data) + object.length;
	}

	char *buffer = new char[(uint32_t)length];
	char *bufferPointer = buffer;

	((uint32_t *)bufferPointer)[0] = nameLength;
	bufferPointer += 4;
	memcpy(bufferPointer, this->name.c_str(), nameLength);
	bufferPointer += nameLength;

	((uint32_t *)bufferPointer)[0] = serializedColumns.size();
	bufferPointer += 4;
	for (const auto &object : serializedColumns)
	{
		memcpy(bufferPointer, &object, offsetof(SerializedObject, data));
		bufferPointer += offsetof(SerializedObject, data);
		memcpy(bufferPointer, object.data, (size_t)object.length);
		bufferPointer += object.length;
	}

	((uint32_t *)bufferPointer)[0] = serializedRows.size();
	bufferPointer += 4;
	for (const auto &object : serializedRows)
	{
		memcpy(bufferPointer, &object, offsetof(SerializedObject, data));
		bufferPointer += offsetof(SerializedObject, data);
		memcpy(bufferPointer, object.data, (size_t)object.length);
		bufferPointer += object.length;
	}

	return SerializedObject(ObjectType::TABLE, length, buffer);
}

bool Table::Deserialize(SerializedObject object)
{
	if (object.length <= 0)
	{
		return false;
	}

	if (object.data == null)
	{
		return false;
	}

	char *bufferPointer = (char *)object.data;

	uint32_t nameLength = ((uint32_t *)bufferPointer)[0];
	bufferPointer += 4;
	char *nameBuffer = new char[nameLength + 4];
	((uint32_t *)(nameBuffer + nameLength))[0] = 0;
	memcpy(nameBuffer, bufferPointer, nameLength);
	this->name.clear();
	this->name = String(nameBuffer);
	delete[] nameBuffer;
	bufferPointer += nameLength;
	
	if (this->columns != nullptr)
	{
		this->columns->clear();
	}

	this->columns = new vector<TableColumn>();

	uint32_t columnsCount = ((uint32_t *)bufferPointer)[0];
	bufferPointer += 4;
	for (int i = 0; i < (int)columnsCount; i++)
	{
		SerializedObject object;
		memcpy(&object, bufferPointer, offsetof(SerializedObject, data));
		bufferPointer += offsetof(SerializedObject, data);
		object.data = bufferPointer;
		bufferPointer += object.length;
		TableColumn column = TableColumn(String(), Type::NONE);
		bool result = column.Deserialize(object);
		if (!result)
		{
			return false;
		}
		this->columns->push_back(column);
	}

	if (this->rows.size() != 0)
	{
		this->rows.clear();
	}

	this->rows = list<TableRow *>();

	uint32_t rowsCount = ((uint32_t *)bufferPointer)[0];
	bufferPointer += 4;
	for (int i = 0; i < (int)rowsCount; i++)
	{
		SerializedObject object;
		memcpy(&object, bufferPointer, offsetof(SerializedObject, data));
		bufferPointer += offsetof(SerializedObject, data);
		object.data = bufferPointer;
		bufferPointer += object.length;
		TableRow *row = new TableRow(this->columns, vector<Data>());
		bool result = row->Deserialize(object);
		if (!result)
		{
			return false;
		}
		this->rows.push_back(row);
	}

	return true;
}

String Table::ToString()
{
	String result = String(TEXT("Table\n")) + String(TEXT("Columns: "));

	for (const auto &iterator : *this->columns)
	{
		result += TEXT("\t") + iterator.name;
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
