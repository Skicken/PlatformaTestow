#include "ecpch.h"
#include "AttendanceList.h"

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
