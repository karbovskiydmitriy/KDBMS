#include "Table.hpp"

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

SerializedObject TableColumn::Serialize()
{
	return SerializedObject();
}

bool TableColumn::Deserialize(char *rows)
{
	return false;
}

TableRow::TableRow(vector<TableColumn> *columns, vector<Data> fields)
{
	this->columns = columns;
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

String TableRow::ToString()
{
	String result = "Values: ";
	int i = 0;

	for (const auto &iterator : this->fields)
	{
		String value;

		switch (this->columns->data()[i++].type)
		{
		case Type::BOOL:
			value = String(iterator.value ? "true" : "false");
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
			value = String("Complex type");
			break;
		default:
			value = String("unknown");
			break;
		}

		result += "\t" + value; // TODO !!!
	}

	return result;
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
