#include "ecpch.h"
#include "AttendanceList.h"

AttendanceList::AttendanceList(const Group& group, const std::string& date): group(group),
                                                                             Date(date)
{
}

AttendanceList::AttendanceList(const AttendanceList& other): group(other.group),
                                                             studentIsPresent(other.studentIsPresent),
                                                             Date(other.Date)
{
}

AttendanceList::AttendanceList(AttendanceList&& other) noexcept: group(std::move(other.group)),
                                                                 studentIsPresent(std::move(other.studentIsPresent)),
                                                                 Date(std::move(other.Date))
{
}

AttendanceList& AttendanceList::operator=(const AttendanceList& other)
{
	if (this == &other)
		return *this;
	group = other.group;
	studentIsPresent = other.studentIsPresent;
	Date = other.Date;
	return *this;
}

AttendanceList& AttendanceList::operator=(AttendanceList&& other) noexcept
{
	if (this == &other)
		return *this;
	group = std::move(other.group);
	studentIsPresent = std::move(other.studentIsPresent);
	Date = std::move(other.Date);
	return *this;
}

Group AttendanceList::getGroup() const
{
	return group;
}


std::string AttendanceList::getDate() const
{
	return Date;
}

AttendanceList::AttendanceList(const Group& group) : group(group)
{
}

void AttendanceList::setUserPresent(User& user)
{
	studentIsPresent[user.getID()] = user;
}

void AttendanceList::removeUserPresent(User& user)
{
	studentIsPresent.erase(user.getID());
}

std::vector<User> AttendanceList::getPresentUsers()
{
	std::vector<User> users;
	for (auto& present : this->studentIsPresent)
	{
		users.push_back(present.second);
	}
	return users;
}
