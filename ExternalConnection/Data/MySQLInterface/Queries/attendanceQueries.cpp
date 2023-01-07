#include <ecpch.h>
#include "Data/MySQLInterface/SQL.h"


namespace ExternalData
{
	void MySQL::addAttendanceList(AttendanceList& list)
	{
		const std::string query = "INSERT INTO `attendance_list`(`GROUP_ID`, `USER_ID`, `attendance_date`) VALUES (?,?,CURRENT_DATE())";
		connection_shared connection = getConnection();
		statement_unique insertQuery(connection->prepareStatement(query));

		for(auto user:list.getPresentUsers())
		{
			insertQuery->setString(1, list.getGroup().getID());
			insertQuery->setString(2, user.getID());
			insertQuery->execute();
		}

	}
	void MySQL::deleteAttendanceList(AttendanceList& list)
	{
		const std::string query = "DELETE FROM `attendance_list` WHERE 0`GROUP_ID` = ? and `attendance_date` = ?;";
		connection_shared connection = getConnection();
		statement_unique deleteQuery(connection->prepareStatement(query));
		deleteQuery->execute();
	}

	std::vector<AttendanceList> MySQL::getAllAttendanceLists()
	{
		const std::string query = "SELECT `GROUP_ID`, `USER_ID`, `attendance_date` FROM `attendance_list` GROUP by `GROUP_ID` SORT by `attendance_date`";
		connection_shared connection = getConnection();
		statement_unique selectQuery(connection->prepareStatement(query));
		result_unique result(selectQuery->executeQuery());

		std::vector<AttendanceList> lists;
		std::vector<User> users;
		std::string prevGroupID="";
		while(result->next())
		{
			if (prevGroupID != result->getString(1))
			{
				users.clear();
			}
			prevGroupID = result->getString(1);
		}



		return lists;
	}
}