#pragma once
#include "Groups.h"
#include "users/user.h"

class AttendanceList
{
	public:
		Group getGroup() const;
		std::string getID() const;
		std::string getDate() const;

		AttendanceList(const Group& group);
		void setUserPresent(User& user);
		void removeUserPresent(User& user);
		std::vector<User> getPresentUsers();
	private:
			Group group;
			std::map<std::string, bool> studentIsPresent;
			std::string ID;
			std::string Date;

};

