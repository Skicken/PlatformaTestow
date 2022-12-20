#include "ptpch.h"
#include "SQL.h"

MySQL::MySQL()
{
	Poco::Data::SQLite::Connector::registerConnector();
	this->session = std::make_shared<Session>("SQLite", "Data.db");

}

MySQL::~MySQL()
{
}

