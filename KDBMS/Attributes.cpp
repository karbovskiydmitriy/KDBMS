#include "Attributes.hpp"

Attributes::Attributes(bool nonNull, bool primaryKey, bool foreignKey)
{
	this->nonNull = nonNull;
	this->primaryKey = primaryKey;
	this->foreignKey = foreignKey;
}

String Attributes::ToString()
{
	String result = "Attributes: ";

	bool first = true;

	if (this->nonNull)
	{
		result += "non-null";
		first = false;
	}

	if (this->primaryKey)
	{
		if (!first)
		{
			result += ", ";
		}
		result += "primary key";
		first = false;
	}

	if (this->nonNull)
	{
		if (!first)
		{
			result += ", ";
		}
		result += "foreign key";
		first = false;
	}

	return result;
}
