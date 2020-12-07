#include "Query.hpp"

Response::Response()
{
	this->errorCode = ErrorCode::OK;
	this->data = null;
}

Response::Response(ErrorCode errorCode, Pointer data)
{
	this->errorCode = errorCode;
	this->data = data;
}

Condition::Condition(String column, Data value, Type type, Comparison comparison, Condition *andCondition, Condition *orCondition)
{
	this->column = column;
	this->value = value;
	this->type = type;
	this->comparison = comparison;
	this->andCondition = andCondition;
	this->orCondition = orCondition;
}
