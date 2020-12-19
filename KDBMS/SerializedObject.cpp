#include "SerializedObject.hpp"

SerializedObject::SerializedObject()
{
	this->type = ObjectType::NONE;
	this->primitiveType = Type::NONE;
	this->length = 0;
	this->data = 0;
}

SerializedObject::SerializedObject(ObjectType type, uint64_t length, Pointer data)
{
	this->type = type;
	this->primitiveType = Type::NONE;
	this->length = length;
	this->data = data;
}

SerializedObject::SerializedObject(Type primitiveType, uint64_t length, Pointer data)
{
	this->type = ObjectType::PRIMITIVE;
	this->primitiveType = primitiveType;
	this->length = length;
	this->data = data;
}
