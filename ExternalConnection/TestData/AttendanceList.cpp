#include "ecpch.h"
#include "AttendanceList.h"

AttendanceList::AttendanceList(const Group& group, const std::string& date): group(group),
                                                                             Date(date)
{
}

void AttendanceList::setDate(const std::string& date)
{
	Date = date;
}

AttendanceList::AttendanceList(const AttendanceList& other): group(other.group),
                                                             studentIsPresent(other.studentIsPresent),
                                                             ID(other.ID),
                                                             Date(other.Date)
{
}

AttendanceList::AttendanceList(AttendanceList&& other) noexcept: group(std::move(other.group)),
                                                                 studentIsPresent(std::move(other.studentIsPresent)),
                                                                 ID(std::move(other.ID)),
                                                                 Date(std::move(other.Date))
{
}

AttendanceList& AttendanceList::operator=(const AttendanceList& other)
{
	if (this == &other)
		return *this;
	group = other.group;
	studentIsPresent = other.studentIsPresent;
	ID = other.ID;
	Date = other.Date;
	return *this;
}

AttendanceList& AttendanceList::operator=(AttendanceList&& other) noexcept
{
	if (this == &other)
		return *this;
	group = std::move(other.group);
	studentIsPresent = std::move(other.studentIsPresent);
	ID = std::move(other.ID);
	Date = std::move(other.Date);
	return *this;
}

Group AttendanceList::getGroup() const
{
	return group;
}

std::string AttendanceList::getID() const
{
	return ID;
}

std::string AttendanceList::getDate() const
{
	return Date;
}

AttendanceList::AttendanceList(const Group& group): group(group)
{
}

void AttendanceList::setUserPresent(User& user)
{
	studentIsPresent[user.getID()] = true;
}

void AttendanceList::removeUserPresent(User& user)
{
	studentIsPresent.erase(user.getID());
}

void AttendanceList::setUserPresent(std::string userID)
{
	studentIsPresent[userID] = true;

}

void AttendanceList::removeUserPresent(std::string userID)
{
	studentIsPresent.erase(userID);

}
std::vector<User> AttendanceList::getPresentUsers()
{
	std::vector<User> users;
	for (auto& present : this->studentIsPresent)
	{
		if (present.second)
		{
			for(auto user:this->group.getUsers())
			{
				if (user.getID() == present.first)
					users.push_back(user);
			}
		}
	}
	return users;
}
