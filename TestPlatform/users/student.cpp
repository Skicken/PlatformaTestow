#include "ptpch.h"
#include "student.h"


Student::Student(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid):
	User(name,surname,email,uuid)
{
	this->type = UserType::STUDENT; 
}

Student::Student(const std::string& name, const std::string& surname, const std::string& email): User(name, surname, email)
{
	this->type = UserType::STUDENT;
}

