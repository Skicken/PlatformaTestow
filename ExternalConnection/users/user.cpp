#include "ecpch.h"
#include "user.h"

User::User(const User& other): name(other.name),
                               surname(other.surname),
                               email(other.email),
                               ID(other.ID),
                               type(other.type)
{
}

User::User(User&& other) noexcept: name(std::move(other.name)),
                                   surname(std::move(other.surname)),
                                   email(std::move(other.email)),
                                   ID(std::move(other.ID)),
                                   type(other.type)
{
}

User& User::operator=(const User& other)
{
	if (this == &other)
		return *this;
	name = other.name;
	surname = other.surname;
	email = other.email;
	ID = other.ID;
	type = other.type;
	return *this;
}

User& User::operator=(User&& other) noexcept
{
	if (this == &other)
		return *this;
	name = std::move(other.name);
	surname = std::move(other.surname);
	email = std::move(other.email);
	ID = std::move(other.ID);
	type = other.type;
	return *this;
}

void User::setType(const UserType type)
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

User::~User() = default;

User::User(const std::string& name, const std::string& surname, const std::string& 
           email, const std::string& uuid): name(name),
                                            surname(surname),
                                            email(email),
                                            ID(uuid)
{
}

User::User(const std::string& name, const std::string& surname, const std::string& email) :   name(name),
							surname(surname),
							email(email)

{

}
std::string User::getID() const
{
	return ID;
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

UserType User::getType() const
{
	return type;
}
