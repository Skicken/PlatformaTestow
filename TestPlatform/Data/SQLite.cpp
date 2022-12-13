#include "ptpch.h"
#include "SQLite.h"

SQLite::SQLite()
{
	Poco::Data::SQLite::Connector::registerConnector();
	this->session = std::make_shared<Session>("SQLite", "Data.db");
	*this->session << Queries::createUsersTable;

}

SQLite::~SQLite()
{
}

