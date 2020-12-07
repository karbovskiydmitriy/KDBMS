#include "Data.hpp"

Data::Data(Type type, uint64_t data)
{
	if ((uint32_t)type | (uint32_t)Type::ARRAY)
	{
		pointer = (Pointer)data;
	}
	else
	{
		switch (type)
		{
		case Type::BOOL:
			value = (bool)data;
			break;
		case Type::CHAR:
			value = (char)data;
			break;
		case Type::BYTE:
			value = (signed char)data;
			break;
		case Type::UBYTE:
			value = (unsigned char)data;
			break;
		case Type::SHORT:
			value = (signed short int)data;
			break;
		case Type::USHORT:
			value = (unsigned short int)data;
			break;
		case Type::INT:
			value = (signed long int)data;
			break;
		case Type::UINT:
			value = (unsigned long int)data;
			break;
		case Type::LONG:
			value = (signed long long int)data;
			break;
		case Type::ULONG:
			value = (unsigned long long int)data;
			break;
		case Type::FLOAT:
			singlePrecisionFloating = *(float *)&data;
			break;
		case Type::DOUBLE:
			doublePrecisionFloating = *(double *)&data;
			break;
		case Type::STRING:
			pointer = (String *)data;
			break;
		case Type::ENUM:
			pointer = (Enum *)data;
			break;
		case Type::DATE:
			pointer = (Date *)data;
			break;
		case Type::TIME:
			pointer = (Time *)data;
			break;
		case Type::DATETIME:
			pointer = (DateTime *)data;
			break;
		case Type::BLOB:
			pointer = (Blob *)data;
			break;
		default:
			value = 0;
			break;
		}
	}
}

Data::Data(bool data)
{
	value = data;
}

Data::Data(char data)
{
	value = data;
}

Data::Data(signed char data)
{
	value = data;
}

Data::Data(unsigned char data)
{
	value = data;
}

Data::Data(signed short int data)
{
	value = data;
}

Data::Data(unsigned short int data)
{
	value = data;
}

Data::Data(signed long int data)
{
	value = data;
}

Data::Data(unsigned long int data)
{
	value = data;
}

Data::Data(signed long long int data)
{
	value = data;
}

Data::Data(unsigned long long int data)
{
	value = data;
}

Data::Data(float data)
{
	singlePrecisionFloating = data;
}

Data::Data(double data)
{
	doublePrecisionFloating = data;
}

Data::Data(String *data)
{
	pointer = data;
}

Data::Data(Enum *data)
{
	pointer = data;
}

Data::Data(Date *data)
{
	pointer = data;
}

Data::Data(Time *data)
{
	pointer = data;
}

Data::Data(DateTime *data)
{
	pointer = data;
}

Data::Data(Blob *data)
{
	pointer = data;
}

Data::Data(Pointer *array)
{
	pointer = array;
}
