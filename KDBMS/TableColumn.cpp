#include "TableColumn.hpp"

TableColumn::TableColumn()
{
	this->type = Type::NONE;
	this->attributes = 0;
}

TableColumn::TableColumn(String name, Type type, Attributes attributes)
{
	this->name = name;
	this->type = type;
	this->attributes = attributes;
}

SerializedObject TableColumn::Serialize()
{
	uint32_t nameLength = Strlen(this->name.c_str());
	int length = 4 + nameLength + sizeof(Type) + sizeof(Attributes);

	char *buffer = new char[length];
	char *bufferPointer = buffer;

	((uint32_t *)bufferPointer)[0] = nameLength;
	bufferPointer += 4;
	memcpy(bufferPointer, this->name.c_str(), nameLength);
	bufferPointer += nameLength;
	memcpy(bufferPointer, &this->type, sizeof(Type));
	bufferPointer += sizeof(Type);
	memcpy(bufferPointer, &this->attributes, sizeof(Attributes));

	return SerializedObject(ObjectType::COLUMN, length, buffer);
}

bool TableColumn::Deserialize(SerializedObject object)
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

	memcpy(&this->type, bufferPointer, sizeof(Type));
	bufferPointer += sizeof(Type);

	memcpy(&this->attributes, bufferPointer, sizeof(Attributes));

	return true;
}
