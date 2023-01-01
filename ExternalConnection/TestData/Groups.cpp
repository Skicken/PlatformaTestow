#include "ecpch.h"
#include "Groups.h"

void Group::setName(const std::string& name)
{
	this->name = name;
}

void Group::setUsers(const std::vector<User>& users)
{
	this->users = users;
}

std::string Group::getID() const
{
	return ID;
}

std::string Group::getName() const
{
	return name;
}

std::vector<User> Group::getUsers() const
{
	return users;
}
