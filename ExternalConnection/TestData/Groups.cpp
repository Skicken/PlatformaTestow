#include "ecpch.h"
#include "Groups.h"

Group::Group(const std::string& name, const std::vector<User>& users): name(name),
                                                                       users(users)
{
}

Group::Group(const std::string& id, const std::string& name, const std::vector<User>& users): ID(id),
	name(name),
	users(users)
{
}

Group::Group(const Group& other): ID(other.ID),
                                  name(other.name),
                                  users(other.users)
{
}

Group::Group(Group&& other) noexcept: ID(std::move(other.ID)),
                                      name(std::move(other.name)),
                                      users(std::move(other.users))
{
}

Group& Group::operator=(const Group& other)
{
	if (this == &other)
		return *this;
	ID = other.ID;
	name = other.name;
	users = other.users;
	return *this;
}

Group& Group::operator=(Group&& other) noexcept
{
	if (this == &other)
		return *this;
	ID = std::move(other.ID);
	name = std::move(other.name);
	users = std::move(other.users);
	return *this;
}

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
