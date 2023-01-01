#pragma once
#include "users/user.h"

class Group
{
	public:
		void setName(const std::string& name);
		void setUsers(const std::vector<User>& users);

		std::string getID() const;
		std::string getName() const;
		std::vector<User> getUsers() const;
	private:
		std::string ID;
		std::string name;
		std::vector<User> users;

};

