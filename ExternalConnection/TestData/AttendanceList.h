#pragma once
#include "Groups.h"
#include "users/user.h"

class AttendanceList
{
public:
		AttendanceList(const Group& group, const std::string& date);
		void setDate(const std::string& date);
		AttendanceList(const AttendanceList& other);
		AttendanceList(AttendanceList&& other) noexcept;
		AttendanceList& operator=(const AttendanceList& other);
		AttendanceList& operator=(AttendanceList&& other) noexcept;

		Group getGroup() const;
		std::string getID() const;
		std::string getDate() const;

		AttendanceList(const Group& group);
		void setUserPresent(User& user);
		void removeUserPresent(User& user);

		void setUserPresent(std::string userID);
		void removeUserPresent(std::string userID);
		std::vector<User> getPresentUsers();
	private:
			Group group;
			std::map<std::string, bool> studentIsPresent;
			std::string ID;
			std::string Date;

};

