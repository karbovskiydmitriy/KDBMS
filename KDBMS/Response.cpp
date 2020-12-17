#include "Response.hpp"

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
