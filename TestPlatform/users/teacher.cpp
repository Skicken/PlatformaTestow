#include "ptpch.h"
#include "teacher.h"

Teacher::Teacher(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid): User(name, surname, email, uuid)
{
	this->type = UserType::TEACHER;
}

Teacher::Teacher(const std::string& name, const std::string& surname, const std::string& email): User(name, surname, email)
{
	this->type = UserType::TEACHER;
}

