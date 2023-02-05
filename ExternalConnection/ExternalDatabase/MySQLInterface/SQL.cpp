#include "ecpch.h"
#include "SQL.h"

#include "Helpers/Utilities.h"

namespace ExternalData {
	std::shared_ptr<sql::Connection> MySQL::getConnection()
	{
		connection_shared connection;
		try
		{
			connection = connection_shared((driver->connect(serverIP, "root", "")));
			connection->setSchema("data");
		}
		catch (sql::SQLException& exception) {
			throw DatabaseException(ExceptionType::CANNOT_CONNECT, "cannot connect to database");
		}
		return connection;
	}

	std::string MySQL::getUniqueID()
	{
		connection_shared connection = getConnection();
		return Utilities::generateID(connection);
	}

	std::string MySQL::getCurrentDate()
	{
		connection_shared connection = getConnection();
		const std::string query = "SELECT CURRENT_DATE()";
		statement_unique statement(connection->prepareStatement(query));
		result_unique result(statement->executeQuery());
		if (result->next())
		{
			return result->getString(1);
		}
		return "";
	}

	MySQL::MySQL() :
		driver(sql::mysql::get_driver_instance())
	{
	}
	MySQL::~MySQL()
	{
	}




}
