#pragma once
#include "DataInterface.h"
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

class MySQL : public DataInterface
{
	private:
	std::shared_ptr <Session> session;
	public:
		MySQL();
		~MySQL();
};

