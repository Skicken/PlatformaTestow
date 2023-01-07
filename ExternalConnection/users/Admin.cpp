#include "ecpch.h"
#include "Admin.h"

Admin::Admin(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid): Teacher(name, surname, email, uuid)
{
	this->type = UserType::ADMIN;

}

Admin::Admin(const std::string& name, const std::string& surname, const std::string& email): Teacher(name, surname, email)
{
	this->type = UserType::ADMIN;
}
