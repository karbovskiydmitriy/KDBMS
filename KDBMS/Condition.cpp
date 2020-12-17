#include "Condition.hpp"

Condition::Condition(Table *table, String column, Data data, Comparison comparison, Condition *andCondition, Condition *orCondition)
{
	this->index = table->GetColumnIndex(column);
	this->type = table->GetColumnType(column);
	this->data = data;
	this->comparison = comparison;
	this->andCondition = andCondition;
	this->orCondition = orCondition;
}

bool Condition::Check(vector<Data> row)
{
	bool result = false;

	if (index == -1)
	{
		return false;
	}

	if (this->type == Type::NONE)
	{
		return false;
	}

	Data rowData = row.data()[this->index];

	switch (this->comparison)
	{
	case Comparison::EQUALS:
		switch (this->type)
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
			return rowData.value == this->data.value;
		case Type::STRING:
			return ((String *)rowData.pointer) == ((String *)this->data.pointer);
		case Type::BLOB:
		{
			Blob *b1 = ((Blob *)rowData.pointer);
			Blob *b2 = ((Blob *)this->data.pointer);
			if (b1->size() == b2->size())
			{
				if (memcmp(b1->data(), b2->data(), b1->size()) == 0)
				{
					return true;
				}
			}

			return false;
		}
		default:
			return false;
		}
	case Comparison::NOT_EQUALS:
		switch (this->type)
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
			return rowData.value != this->data.value;
		case Type::STRING:
			return ((String *)rowData.pointer) != ((String *)this->data.pointer);
		case Type::BLOB:
		{
			Blob *b1 = ((Blob *)rowData.pointer);
			Blob *b2 = ((Blob *)this->data.pointer);
			if (b1->size() == b2->size())
			{
				if (memcmp(b1->data(), b2->data(), b1->size()) != 0)
				{
					return true;
				}
			}
			else
			{
				return true;
			}

			return false;
		}
		default:
			return false;
		}
	case Comparison::LESS_THAN:
		switch (this->type)
		{
		case Type::LONG:
		case Type::BYTE:
		case Type::SHORT:
		case Type::INT:
			return (signed long long int)rowData.value < (signed long long int)this->data.value;
		case Type::CHAR:
		case Type::UBYTE:
		case Type::USHORT:
		case Type::UINT:
		case Type::ULONG:
			return (unsigned long long int)rowData.value < (unsigned long long int)this->data.value;
		case Type::FLOAT:
			return rowData.singlePrecisionFloating < this->data.singlePrecisionFloating;
		case Type::DOUBLE:
			return rowData.doublePrecisionFloating < this->data.doublePrecisionFloating;
		default:
			return false;
		}
	case Comparison::LESS_OR_EQUALS_THAN:
		switch (this->type)
		{
		case Type::LONG:
		case Type::BYTE:
		case Type::SHORT:
		case Type::INT:
			return (signed long long int)rowData.value <= (signed long long int)this->data.value;
		case Type::CHAR:
		case Type::UBYTE:
		case Type::USHORT:
		case Type::UINT:
		case Type::ULONG:
			return (unsigned long long int)rowData.value <= (unsigned long long int)this->data.value;
		case Type::FLOAT:
			return rowData.singlePrecisionFloating <= this->data.singlePrecisionFloating;
		case Type::DOUBLE:
			return rowData.doublePrecisionFloating <= this->data.doublePrecisionFloating;
		default:
			return false;
		}
	case Comparison::GREATER_THAN:
		switch (this->type)
		{
		case Type::LONG:
		case Type::BYTE:
		case Type::SHORT:
		case Type::INT:
			return (signed long long int)rowData.value > (signed long long int)this->data.value;
		case Type::CHAR:
		case Type::UBYTE:
		case Type::USHORT:
		case Type::UINT:
		case Type::ULONG:
			return (unsigned long long int)rowData.value > (unsigned long long int)this->data.value;
		case Type::FLOAT:
			return rowData.singlePrecisionFloating > this->data.singlePrecisionFloating;
		case Type::DOUBLE:
			return rowData.doublePrecisionFloating > this->data.doublePrecisionFloating;
		default:
			return false;
		}
	case Comparison::GREATER_OR_EQUALS_THAN:
		switch (this->type)
		{
		case Type::LONG:
		case Type::BYTE:
		case Type::SHORT:
		case Type::INT:
			return (signed long long int)rowData.value >= (signed long long int)this->data.value;
		case Type::CHAR:
		case Type::UBYTE:
		case Type::USHORT:
		case Type::UINT:
		case Type::ULONG:
			return (unsigned long long int)rowData.value >= (unsigned long long int)this->data.value;
		case Type::FLOAT:
			return rowData.singlePrecisionFloating >= this->data.singlePrecisionFloating;
		case Type::DOUBLE:
			return rowData.doublePrecisionFloating >= this->data.doublePrecisionFloating;
		default:
			return false;
		}
	default:
		return false;
	}

	if (!result)
	{
		if (this->orCondition != nullptr)
		{
			result = this->orCondition->Check(row);

			if (result)
			{
				return true;
			}
		}
	}

	if (result)
	{
		if (this->andCondition != nullptr)
		{
			result = this->andCondition->Check(row);
		}
	}

	return result;
}
