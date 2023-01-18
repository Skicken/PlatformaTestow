#include "ecpch.h"
#include "DataInterface.h"

namespace ExternalData
{
	UserType StringToEnum(std::string value)
	{
		if (value == "student")
			return UserType::STUDENT;
		else if (value == "teacher")
			return UserType::TEACHER;
		else
			return UserType::ADMIN;
	}
	std::string EnumToString(UserType type)
	{
		switch (type) {
		case UserType::STUDENT:
			return "student";
		case UserType::TEACHER:
			return "teacher";
		case UserType::ADMIN:
			return "admin";
		}
		return "";
	}
}