#include <ecpch.h>
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "TestData/Homework.h"

namespace ExternalData {
	void MySQL::addHomework(Group& group, Homework& homework)
	{
		connection_shared connection = getConnection();
		const std::string query = "INSERT INTO `homework`(`ID`, `GROUP_ID`, `QUESTION`) VALUES("+ID_GEN+" , ? , ? )";
		statement_unique statement(connection->prepareStatement(query));
		statement->setString(1, group.getID());
		statement->setString(2, homework.getQuestion());
		statement->execute();

	}
	std::vector<Homework> MySQL::getAllHomework()
	{
		connection_shared connection = getConnection();
		const std::string query = "SELECT `ID`,`QUESTION` FROM `homework`";
		statement_unique statement(connection->prepareStatement(query));
		result_unique result(statement->executeQuery());
		std::vector<Homework> homework;
		while(result->next())
		{
			homework.push_back(Homework(result->getString(1), result->getString(2)));
		}
		return homework;


	}
	void MySQL::commitHomework(std::string StudentID, HomeworkCommit& homework)
	{
		connection_shared connection = getConnection();
		const std::string query = "INSERT INTO `user_homework`(`USER_ID`, `HOMEWORK_ID`, `ANSWER`, `DATE`) VALUES (?,?,?,NULL);";
		statement_unique statement(connection->prepareStatement(query));

		statement->setString(1, StudentID);
		statement->setString(2, homework.getID());
		statement->setString(3, homework.getAnswer());
		statement->execute();

	}

	std::vector<HomeworkCommit> MySQL::getCommitHomework(std::string STUDENT_ID)
	{
		connection_shared connection = getConnection();
		const std::string query = "SELECT `HOMEWORK_ID`, homework.QUESTION,`ANSWER`, `DATE` FROM `user_homework` INNER JOIN homework on user_homework.HOMEWORK_ID = homework.ID WHERE USER_ID = ?";
		statement_unique statement(connection->prepareStatement(query));
		statement->setString(1, STUDENT_ID);
		result_unique result(statement->executeQuery());
		std::vector<HomeworkCommit> homeworkCommit;
		while(result->next())
		{
			homeworkCommit.push_back(HomeworkCommit(result->getString(1),
				result->getString(2), result->getString(3), result->getString(4)
			));
		}
		return homeworkCommit;

	}
	std::vector<HomeworkCommit> MySQL::getCommitHomework(Homework homework)
	{
		connection_shared connection = getConnection();
		const std::string query = "SELECT `HOMEWORK_ID`, homework.QUESTION,`ANSWER`, `DATE` FROM `user_homework` INNER JOIN homework on user_homework.HOMEWORK_ID = homework.ID WHERE HOMEWORK_ID = ?";
		statement_unique statement(connection->prepareStatement(query));
		statement->setString(1, homework.getID());
		result_unique result(statement->executeQuery());
		std::vector<HomeworkCommit> homeworkCommit;
		while (result->next())
		{
			homeworkCommit.push_back(HomeworkCommit(result->getString(1),
				result->getString(2), result->getString(3), result->getString(4)
			));
		}
		return homeworkCommit;
	}
	void MySQL::deleteHomework(Homework& homework)
	{
		connection_shared connection = getConnection();
		const std::string query = "DELETE FROM `homework` WHERE `ID` = ?";
		statement_unique statement(connection->prepareStatement(query));
		statement->setString(1, homework.getID());
		statement->execute();
	}
}
