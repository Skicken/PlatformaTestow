#pragma once
#include "user.h"

class Teacher :
    public User
{
    public:
	Teacher(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid);

	Teacher(const std::string& name, const std::string& surname, const std::string& email);

};

