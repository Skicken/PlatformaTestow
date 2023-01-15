#pragma once
#include "ExternalDatabase/MySQLInterface/SQL.h"

namespace ExternalData
{
	class UserFactory
	{
		public:
			static UserType StringToEnum(std::string value);
			static std::string EnumToString(UserType type);
			std::shared_ptr<User> createUserFrom(const std::string& name, const std::string& surname, const		std::string& email, const std::string& id,
				const std::string& type);
			User getUserFromRow(result_shared result);
			User getUserFromID(connection_shared connection,std::string ID);

	};
}
