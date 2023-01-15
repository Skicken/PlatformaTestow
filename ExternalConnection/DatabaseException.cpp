#include "ecpch.h"
#include "DatabaseException.h"


ExternalData::DatabaseException::DatabaseException(ExceptionType type, const std::string& message): type(type),
	message(message) 
{
}

ExternalData::DatabaseException::~DatabaseException() noexcept
{
}

char const* ExternalData::DatabaseException::what() const
{
	return message.c_str();
}

ExternalData::ExceptionType ExternalData::DatabaseException::getType() const
{
	return type;
}
