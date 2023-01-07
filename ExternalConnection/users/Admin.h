#pragma once
#include <Users/Teacher.h>
class Admin : public Teacher
{
	public:
		Admin(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid);
		Admin(const std::string& name, const std::string& surname, const std::string& email);
};

