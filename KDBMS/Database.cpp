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

Response Database::FindTable(String name)
{
	Table *table = FindTableByName(name);

	if (table != nullptr)
	{
		return Response(ErrorCode::OK, table);
	}

	return Response(ErrorCode::NOT_FOUND);
}

Response Database::SaveToFile(String fileName)
{
	SerializedObject object = this->Serialize();

	vector<byte> *data = new vector<byte>((const unsigned int)object.length);
	memcpy(data->data(), object.data, (size_t)object.length);
	WriteToFile(fileName, data);
	delete data;

	return Response(ErrorCode::OK);
}

Response Database::LoadFromFile(String fileName)
{
	vector<byte> *data = ReadFromFile(fileName);

	if (data != nullptr)
	{
		bool result = this->Deserialize(SerializedObject(ObjectType::DATABASE, data->size(), data->data()));

		delete data;

		if (!result)
		{	
			return Response(ErrorCode::SERIALIZATION_ERROR);
		}

		return Response(ErrorCode::OK);
	}

	return Response(ErrorCode::NOT_FOUND);
}

SerializedObject Database::Serialize()
{
	uint32_t nameLength = Strlen(this->name.c_str());
	uint64_t length = 8ull + nameLength;

	vector<SerializedObject> serializedTables;
	for (const auto &table : *this->tables)
	{
		SerializedObject object = table->Serialize();
		serializedTables.push_back(object);
		length += offsetof(SerializedObject, data) + object.length;
	}

	char *buffer = new char[(uint32_t)length];
	char *bufferPointer = buffer;

	((uint32_t *)bufferPointer)[0] = nameLength;
	bufferPointer += 4;
	memcpy(bufferPointer, this->name.c_str(), nameLength);
	bufferPointer += nameLength;

	((uint32_t *)bufferPointer)[0] = serializedTables.size();
	bufferPointer += 4;
	for (const auto &object : serializedTables)
	{
		memcpy(bufferPointer, &object, offsetof(SerializedObject, data));
		bufferPointer += offsetof(SerializedObject, data);
		memcpy(bufferPointer, object.data, (size_t)object.length);
		bufferPointer += object.length;
	}

	return SerializedObject(ObjectType::TABLE, length, buffer);
}

bool Database::Deserialize(SerializedObject object)
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

	if (this->tables != nullptr)
	{
		this->tables->clear();
	}

	this->tables = new list<Table *>();

	uint32_t tablesCount = ((uint32_t *)bufferPointer)[0];
	bufferPointer += 4;
	for (int i = 0; i < (int)tablesCount; i++)
	{
		SerializedObject object;
		memcpy(&object, bufferPointer, offsetof(SerializedObject, data));
		bufferPointer += offsetof(SerializedObject, data);
		object.data = bufferPointer;
		bufferPointer += object.length;
		Table *table = new Table(String(), nullptr);
		bool result = table->Deserialize(object);
		if (!result)
		{
			return false;
		}
		this->tables->push_back(table);
	}

	return true;
}

String Database::ToString()
{
	String result = String(TEXT("Database: ")) + this->name + String(TEXT("\nTables: "));

	if (this->tables != nullptr && this->tables->size() != 0)
	{
		for (const auto &iterator : *this->tables)
		{
			result += TEXT("\n") + iterator->name;
		}
	}
	else
	{
		result += TEXT("no tables!");
	}

	return result;
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
