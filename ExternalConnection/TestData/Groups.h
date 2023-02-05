#pragma once
#include "users/user.h"

namespace ExternalData
{
	class MySQL;
}
class Group
{
	public:
	Group(const std::string& name);
	Group(const Group& other);
	Group(Group&& other) noexcept;
	Group& operator=(const Group& other);
	Group& operator=(Group&& other) noexcept;

	Group(const std::string& name, const std::vector<User>& users);

	void setName(const std::string& name);
	void setUsers(const std::vector<User>& users);

	std::string getID() const;
	std::string getName() const;
	std::vector<User> getUsers() const;
	private:
		std::string ID;
		std::string name;
		std::vector<User> users;
		Group(const std::string& id, const std::string& name, const std::vector<User>& users);
		friend class ExternalData::MySQL;


};

