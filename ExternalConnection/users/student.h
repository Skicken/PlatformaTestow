#pragma once
#include "user.h"
class Student :
    public User
{
	public:
		Student(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid);
		Student(const std::string& name, const std::string& surname, const std::string& email);
};

