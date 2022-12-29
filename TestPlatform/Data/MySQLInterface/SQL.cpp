#include "ptpch.h"
#include "SQL.h"
namespace ExternalData {
	std::shared_ptr<sql::Connection> MySQL::getConnection()
	{
		connection_ptr connection = connection_ptr((driver->connect(serverIP, "root", "")));
		connection->setSchema("data");
		return connection;
	}
	MySQL::MySQL() :
		driver(sql::mysql::get_driver_instance())
	{
		connection_ptr connection = this->getConnection();
		if (!connection->isValid())
		{
			ERROR("Could not connect with database");
		}
		else
		{
			INFO("Sucesfully connected with database!");
			INFO("Disconecting...");
		}
	}
	MySQL::~MySQL() {}

	void MySQL::commitTestResult()
	{
	}

	void MySQL::getResults(User& user)
	{
	}


}