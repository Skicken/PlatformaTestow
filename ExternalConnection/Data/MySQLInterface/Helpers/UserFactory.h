#pragma once
#include "Data/MySQLInterface/SQL.h"
#include "users/student.h"
#include "users/teacher.h"
#include "users/Admin.h"
namespace ExternalData
{
	class UserFactory
	{
		public:
			static UserType StringToEnum(std::string value);
			static std::string EnumToString(UserType type);
			User* createUserFrom(const std::string& name, const std::string& surname, const		std::string& email, const std::string& id,
				const std::string& type);
			User getUserFromRow(result_shared result);

	};
}
