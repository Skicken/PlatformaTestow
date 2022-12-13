#pragma once
#include "DataInterface.h"
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

class SQLite : public DataInterface
{
	private:
	std::shared_ptr <Session> session;
	struct Queries
	{
		static const std::string createUsersTable;
	};
	public:
		SQLite();
		~SQLite();
};

