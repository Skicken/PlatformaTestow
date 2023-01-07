#include "ecpch.h"
#include "SQL.h"
namespace ExternalData {
	std::shared_ptr<sql::Connection> MySQL::getConnection()
	{
		connection_shared connection = connection_shared((driver->connect(serverIP, "root", "")));
		connection->setSchema("data");
		return connection;
	}
	MySQL::MySQL() :
		driver(sql::mysql::get_driver_instance())
	{

	}
	MySQL::~MySQL() {}




}