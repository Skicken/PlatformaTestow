#include <ecpch.h>
#include "Data/MySQLInterface/SQL.h"


namespace ExternalData
{
	void MySQL::addAttendanceList(AttendanceList& list)
	{
		const std::string query = "INSERT INTO `attendance_list`(`GROUP_ID`, `USER_ID`, `attendance_date`) VALUES (?,?,CURRENT_DATE())";
		connection_shared connection = getConnection();
		statement_unique insertQuery(connection->prepareStatement(query));

		for(const auto& user:list.getPresentUsers())
		{
			insertQuery->setString(1, list.getGroup().getID());
			insertQuery->setString(2, user.getID());
			insertQuery->execute();
		}

	}
	void MySQL::deleteAttendanceList(AttendanceList& list)
	{
		const std::string deleteQuery = "DELETE FROM `attendance_list` WHERE `GROUP_ID` = ? and `attendance_date` = ?;";
		connection_shared connection = getConnection();
		statement_unique deleteStatement(connection->prepareStatement(deleteQuery));
		deleteStatement->setString(1, list.getGroup().getID());
		deleteStatement->setString(2, list.getDate());
		deleteStatement->execute();
	}

	AttendanceList MySQL::getAttendanceList(Group& group, std::string& Date)
	{
		connection_shared connection = getConnection();
		AttendanceList list(group, Date);
		std::string query = "SELECT `USER_ID` FROM `attendance_list` WHERE `GROUP_ID` = ? and `attendance_date` = ?";
		statement_unique statement(connection->prepareStatement(query));
		statement->setString(1, group.getID());
		statement->setString(2, Date);

		result_shared result(statement->executeQuery());
		while(result->next())
		{
			std::string userID = result->getString(1);
			list.setUserPresent(userID);
		}
		return list;
	}


}
