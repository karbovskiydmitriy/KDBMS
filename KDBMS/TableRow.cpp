#include "TableRow.hpp"

TableRow::TableRow()
{
	this->columns = nullptr;
	this->fields = vector<Data>();
}

TableRow::TableRow(vector<TableColumn> *columns, vector<Data> fields)
{
	this->columns = columns;
	this->fields = fields;
}

SerializedObject TableRow::Serialize()
{
	int length = 0;

	for (int i = 0; i < (int)this->columns->size(); i++)
	{
		switch (this->columns->data()[i].type)
		{
		case Type::BOOL:
		case Type::CHAR:
		case Type::BYTE:
		case Type::UBYTE:
		case Type::SHORT:
		case Type::USHORT:
		case Type::INT:
		case Type::UINT:
		case Type::LONG:
		case Type::ULONG:
		case Type::FLOAT:
		case Type::DOUBLE:
			length += sizeof(Data);
			break;
		case Type::STRING:
		{
			const char *str = ((String *)this->fields.data()[i].pointer)->c_str();
			length += 4 + Strlen(str);
		}
		break;
		case Type::DATE:
			length += sizeof(Date);
			break;
		case Type::TIME:
			length += sizeof(Time);
			break;
		case Type::DATETIME:
			length += sizeof(DateTime);
			break;
		case Type::BLOB:
			length += 4 + ((Blob *)this->fields.data()[i].pointer)->size();
			break;
		default:
			// TODO
			break;
		}
	}

	char *buffer = new char[length];
	char *bufferPointer = buffer;

	for (int i = 0; i < (int)this->columns->size(); i++)
	{
		switch (this->columns->data()[i].type)
		{
		case Type::BOOL:
		case Type::CHAR:
		case Type::BYTE:
		case Type::UBYTE:
		case Type::SHORT:
		case Type::USHORT:
		case Type::INT:
		case Type::UINT:
		case Type::LONG:
		case Type::ULONG:
		case Type::FLOAT:
		case Type::DOUBLE:
		{
			((Data *)bufferPointer)[0] = this->fields.data()[i];
			bufferPointer += sizeof(Data);
		}
		break;
		case Type::STRING:
		{
			String *str = (String *)this->fields.data()[i].pointer;
			uint32_t stringLength = str->length();
			((uint32_t *)bufferPointer)[0] = stringLength;
			bufferPointer += 4;
			memcpy(bufferPointer, str->c_str(), stringLength);
			bufferPointer += stringLength;
		}
		break;
		case Type::DATE:
		{
			((Date *)bufferPointer)[0] = ((Date *)this->fields.data()[i].pointer)[0];
			bufferPointer += sizeof(Date);
		}
		break;
		case Type::TIME:
		{
			((Time *)bufferPointer)[0] = ((Time *)this->fields.data()[i].pointer)[0];
			bufferPointer += sizeof(Time);
		}
		break;
		case Type::DATETIME:
		{
			((DateTime *)bufferPointer)[0] = ((DateTime *)this->fields.data()[i].pointer)[0];
			bufferPointer += sizeof(DateTime);
		}
		break;
		case Type::BLOB:
		{
			Blob *blob = (Blob *)this->fields.data()[i].pointer;
			((uint32_t *)bufferPointer)[0] = blob->size();
			bufferPointer += 4;
			memcpy(bufferPointer, blob->data(), blob->size());
			bufferPointer += blob->size();
		}
		break;
		default:
			// TODO
			break;
		}
	}

	return SerializedObject(ObjectType::ROW, length, buffer);
}

bool TableRow::Deserialize(SerializedObject object)
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

	this->fields.clear();

	for (int i = 0; i < (int)this->columns->size(); i++)
	{
		Data data;
		switch (this->columns->data()[i].type)
		{
		case Type::BOOL:
		case Type::CHAR:
		case Type::BYTE:
		case Type::UBYTE:
		case Type::SHORT:
		case Type::USHORT:
		case Type::INT:
		case Type::UINT:
		case Type::LONG:
		case Type::ULONG:
		case Type::FLOAT:
		case Type::DOUBLE:
		{
			memcpy(&data.value, bufferPointer, sizeof(Data));
			bufferPointer += sizeof(Data);
		}
		break;
		case Type::STRING:
		{
			uint32_t stringLength = ((uint32_t *)bufferPointer)[0];
			char *buffer = new char[stringLength + 4];
			((uint32_t *)(buffer + stringLength))[0] = 0;
			bufferPointer += 4;
			memcpy(buffer, bufferPointer, stringLength);
			data.pointer = new String(buffer);
			delete[] buffer;
			bufferPointer += stringLength;
		}
		break;
		case Type::DATE:
		{
			data.pointer = new Date((const Date &)bufferPointer);
			bufferPointer += sizeof(Date);
		}
		break;
		case Type::TIME:
		{
			data.pointer = new Time((const Time &)bufferPointer);
			bufferPointer += sizeof(Time);
		}
		break;
		case Type::DATETIME:
		{
			data.pointer = new DateTime((const DateTime &)bufferPointer);
			bufferPointer += sizeof(DateTime);
		}
		break;
		case Type::BLOB:
		{
			uint32_t blobLength = ((uint32_t *)bufferPointer)[0];
			char *buffer = new char[blobLength];
			bufferPointer += 4;
			memcpy(buffer, bufferPointer, blobLength);
			data.pointer = new Blob((const size_t)blobLength, (const char &)buffer);
			bufferPointer += blobLength;
		}
		break;
		default:
			// TODO
			break;
		}
		this->fields.push_back(data);
	}

	return true;
}

String TableRow::ToString()
{
	String result = TEXT("Values: ");
	int i = 0;

	for (const auto &iterator : this->fields)
	{
		String value;

		switch (this->columns->data()[i++].type)
		{
		case Type::BOOL:
			value = String(iterator.value ? TEXT("true") : TEXT("false"));
			break;
		case Type::CHAR:
			value = String((const char *)&iterator.value);
			break;
		case Type::BYTE:
		case Type::SHORT:
		case Type::INT:
		case Type::LONG:
			value = To_String((long long)iterator.value);
			break;
		case Type::UBYTE:
		case Type::USHORT:
		case Type::UINT:
		case Type::ULONG:
			value = To_String((unsigned long long)iterator.value);
			break;
		case Type::FLOAT:
			value = To_String((float)iterator.value);
			break;
		case Type::DOUBLE:
			value = To_String((double)iterator.value);
			break;
		case Type::STRING:
			value = *(String *)iterator.pointer;
			break;
		case Type::ENUM:
		case Type::DATE:
		case Type::TIME:
		case Type::DATETIME:
		case Type::BLOB:
			value = String(TEXT("Complex type"));
			break;
		default:
			value = String(TEXT("unknown"));
			break;
		}

		result += TEXT("\t") + value; // TODO !!!
	}

	return result;
}
