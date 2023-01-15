#include <ecpch.h>
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "ExternalDatabase/MySQLInterface/Helpers/UserFactory.h"

namespace ExternalData
{
	void MySQL::addGroup(Group& group)
	{
		const connection_shared connection = getConnection();

		std::string groupID = getUniqueID();
		const std::string insertGroupQuery = "INSERT INTO `groups`(`ID`, `name`) VALUES (?,?)";
		const statement_unique insertGroup(connection->prepareStatement(insertGroupQuery));
		insertGroup->setString(1, groupID);
		insertGroup->setString(2, group.getName());
		insertGroup->execute();
		const std::string insertGroupUserQuery = "INSERT INTO `user_groups`(`USER_ID`, `GROUP_ID`) VALUES (?,?)";
		const statement_unique insertGroupUser(connection->prepareStatement(insertGroupUserQuery));
		for(auto& groupUser:group.getUsers())
		{
			insertGroupUser->setString(1, groupUser.getID());
			insertGroupUser->setString(2, groupID);
			insertGroupUser->execute();
		}
	}
	std::vector<Group> MySQL::getAllGroups()
	{
		const connection_shared connection = getConnection();

		const std::string selectGroupQuery = "SELECT `ID`, `name` FROM `groups`";
		statement_unique selectGroup(connection->prepareStatement(selectGroupQuery));
		result_unique result(selectGroup->executeQuery());

		std::vector<Group> groups;
		while(result->next())
		{
			std::string groupID = result->getString(1);
			std::vector<User> users = getGroupUsers(groupID);
			Group group(groupID, result->getString(2),users);
			groups.push_back(group);
		}
		return groups;
	}
	void MySQL::deleteGroup(Group& group)
	{
		const std::string deleteGroupQuery = "DELETE FROM `groups` WHERE `ID` = ?";
		const connection_shared connection = getConnection();
		statement_unique deleteGroup(connection->prepareStatement(deleteGroupQuery));
		deleteGroup->setString(1,group.getID());
		deleteGroup->execute();
	}
	std::vector<User> MySQL::getGroupUsers(std::string groupID)
	{
		connection_shared connection = getConnection();

		const std::unique_ptr<UserFactory> userFactory;
		std::vector<User> users;
		const std::string getUsersQuery = "select name, surname, email, ID, accountType from users inner join user_groups on user_groups.USER_ID = users.id where user_groups.GROUP_ID = ?";
		const statement_unique getUsers(connection->prepareStatement(getUsersQuery));
		getUsers->setString(1, groupID);
		const result_shared usersResult(getUsers->executeQuery());
		while (usersResult->next())
		{
			users.push_back(userFactory->getUserFromRow(usersResult));
		}
		return users;
	}


}
