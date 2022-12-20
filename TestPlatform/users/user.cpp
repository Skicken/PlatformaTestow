#include "ptpch.h"
#include "user.h"

User::UserType User::getType() const
{
	return type;
}
void User::setType(UserType type)
{
	this->type = type;
}

void User::setName(const std::string& name)
{
	this->name = name;
}

void User::setSurname(const std::string& surname)
{
	this->surname = surname;
}

bool User::setEmail(const std::string& email)
{
	this->email = email;
	return true;
}

User::User(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid,
           UserType type): name(name),
                           surname(surname),
                           email(email),
                           uuid(uuid),
                           type(type)
{
}

std::string User::getUUID() const
{
	return uuid;
}

std::string User::getName() const
{
	return name;
}

std::string User::getSurname() const
{
	return surname;
}

std::string User::getEmail() const
{
	return email;
}
