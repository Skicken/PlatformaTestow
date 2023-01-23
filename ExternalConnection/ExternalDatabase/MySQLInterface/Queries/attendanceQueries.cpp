#include <ecpch.h>
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "ExternalDatabase/MySQLInterface/Helpers/UserFactory.h"


namespace ExternalData
{
	void MySQL::addAttendanceList(AttendanceList& list)
	{
		const std::string query = "INSERT INTO `attendance_list`(`GROUP_ID`, `USER_ID`, `attendance_date`) VALUES (?,?,?)";
		connection_shared connection = getConnection();
		statement_unique insertQuery(connection->prepareStatement(query));
		std::string date = "";
		if (list.getDate().empty()) date = getCurrentDate();
		else date = list.getDate();

		try
		{
			for (const auto& user : list.getPresentUsers())
			{
				insertQuery->setString(1, list.getGroup().getID());
				insertQuery->setString(2, user.getID());
				insertQuery->setString(3, date);

				insertQuery->execute();
			}
		}
		catch (sql::SQLException& exception)
		{
			throw DatabaseException(ExceptionType::ENTRY_EXISTS, "Attendance list for this day already exists");
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
		const auto  factory = std::make_unique<UserFactory>();
		while(result->next())
		{
			std::string userID = result->getString(1);
			User user = factory->getUserFromID(connection, userID);
			list.setUserPresent(user);
		}
		return list;
	}
	std::vector<AttendanceList> MySQL::getGroupAttendanceList(Group& group)
	{
		std::vector<AttendanceList> attendance;
		connection_shared connection = getConnection();
		std::string query = "SELECT DISTINCT `attendance_date` FROM `attendance_list` WHERE `GROUP_ID` = ?";
		statement_unique statement(connection->prepareStatement(query));
		statement->setString(1, group.getID());
		result_shared result(statement->executeQuery());
		while (result->next()) {
			std::string Date = result->getString(1);
			attendance.push_back(getAttendanceList(group, Date));
		}
		return attendance;

	}


}
