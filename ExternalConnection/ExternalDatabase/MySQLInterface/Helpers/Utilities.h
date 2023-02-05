#pragma once
#include "ExternalDatabase/MySQLInterface/SQL.h"

namespace ExternalData
{
	class Utilities
	{
		public:
			static std::string generateID(connection_shared connection);
	};
}

