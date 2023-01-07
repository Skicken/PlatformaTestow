#include "ecpch.h"
#include "UserFactory.h"
namespace ExternalData
{
	UserType UserFactory::StringToEnum(std::string value)
	{
		if (value == "student")
			return UserType::STUDENT;
		else if (value == "teacher")
			return UserType::TEACHER;
		else
			return UserType::ADMIN;
	}
	std::string UserFactory::EnumToString(UserType type)
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
	User* UserFactory::createUserFrom(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid, const std::string& type)
	{
		UserType value = StringToEnum(type);
		switch (value)
		{
			case UserType::STUDENT:
				return new Student(name, surname, email, uuid);
			case UserType::TEACHER:
				return new Teacher(name, surname, email, uuid);
			case UserType::ADMIN:
				return new Admin(name, surname, email, uuid);
			default:
				return new Student(name, surname, email, uuid);

		}

	}

	User UserFactory::getUserFromRow(result_shared result)
	{
		User user = *createUserFrom(
			result->getString(1),
			result->getString(2),
			result->getString(3),
			result->getString(4),
			result->getString(5));
		return user;
	}
}
