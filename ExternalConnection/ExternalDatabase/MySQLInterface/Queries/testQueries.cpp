#include "ecpch.h"
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "ExternalDatabase/MySQLInterface/Helpers/TestGetter.h"
#include "ExternalDatabase/MySQLInterface/Helpers/QuestionInserter.h"
#include "ExternalDatabase/MySQLInterface/Helpers/TestValidator.h"

namespace ExternalData
{

	void MySQL:: modifyTest(Test& test, std::string OWNER_ID)
	{
		std::string error;
		if (!(error = TestValidator::validTest(test)).empty())throw  DatabaseException(ExceptionType::INVALID_QUERY, error);

		deleteTest(test);
		addTest(test,OWNER_ID);
	}
	void MySQL::deleteTest(Test& test)
	{
		const connection_shared connection = getConnection();

		const std::string deleteQuestionQuery = "DELETE FROM `questions` WHERE `ID` = ?";
		statement_unique deleteQuestion(connection->prepareStatement(deleteQuestionQuery));
		const std::string deleteTestQuery = "DELETE FROM `tests` WHERE `ID` = ?";
		statement_unique deleteTest(connection->prepareStatement(deleteTestQuery));

		for(auto &question:test.getQuestions())
		{
			if (!question.getQuestionID().empty())
			{
				deleteQuestion->setString(1, question.getQuestionID());
				deleteQuestion->execute();
			}
		}
		deleteTest->setString(1, test.getTestID());
		try
		{
			deleteTest->execute();
		}
		catch(sql::SQLException &exception)
		{
			std::cout << exception.what();
		}

	}
	void MySQL::addTest(Test& test, std::string OWNER_ID)
	{

		connection_shared connection = getConnection();
		std::string testID = getUniqueID();
		const std::string query = "INSERT INTO `tests`(`ID`, `OWNER_ID`, `name`, `randomize`, `description`) VALUES (?,?,?,?,?)";
		statement_unique testQuery(connection->prepareStatement(query));

		testQuery->setString(1, testID);
		testQuery->setString(2, OWNER_ID);
		testQuery->setString(3, test.getTestName());
		testQuery->setBoolean(4, test.getRandomize());
		testQuery->setString(5, test.getDescription());
		testQuery->execute();

		const auto  inserter = std::make_shared<QuestionInserter>(connection);
		inserter->insertQuestions(testID, test.getQuestions());

	}
	std::vector<Test> MySQL::getAllTests()
	{
		connection_shared connection = this->getConnection();
		const auto  testGetter = std::make_unique<TestGetter>(connection);
		const std::string query = "select ID,name,description,randomize from tests";

		statement_unique stat(connection->prepareStatement(query));
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());
		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(testGetter->getTestFromRow(result));
		}
		return tests;

	}
	std::vector<Test> MySQL::getStudentAvailableTest(std::string STUDENT_ID)
	{
		connection_shared connection = this->getConnection();
		const auto factory = std::make_unique<TestGetter>(connection);

		const std::string query = "select tests.ID, tests.name, description, randomize from tests INNER JOIN assigned_tests on tests.ID = assigned_tests.TEST_ID INNER JOIN user_groups on user_groups.GROUP_ID = assigned_tests.GROUP_ID INNER JOIN users on user_groups.USER_ID = users.ID where users.ID = ? ";
		statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, STUDENT_ID);
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());

		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(factory->getTestFromRow(result));
		}
		return tests;
	}
	std::vector<Test> MySQL::getTeacherTests(std::string OWNER_ID)
	{
		connection_shared connection = this->getConnection();
		const auto factory = std::make_unique<TestGetter>(connection);

		const std::string query = "select ID,name,description,randomize from tests where OWNER_ID = ?";
		statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, OWNER_ID);
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());

		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(factory->getTestFromRow(result));
		}
		return tests;

	}
	void MySQL::assignTest(Group& group, Test& test)
	{
		connection_shared connection = this->getConnection();
		const std::string query = "INSERT INTO `assigned_tests`(`TEST_ID`, `GROUP_ID`) VALUES (?,?)";
		statement_unique stat(connection->prepareStatement(query));

		stat->setString(1, test.getTestID());
		stat->setString(2, group.getID());
		stat->execute();
		

	}

	void MySQL::deassignTest(Group& group, Test& test)
	{
		connection_shared connection = this->getConnection();
		const std::string query = "DELETE FROM `assigned_tests` WHERE `TEST_ID` = ? and `GROUP_ID` = ?";
		statement_unique stat(connection->prepareStatement(query));

		stat->setString(1, test.getTestID());
		stat->setString(2, group.getID());
		stat->execute();
	}

	std::vector<Test> MySQL::getAllAssignedTests(Group& group,User& owner)
	{
		connection_shared connection = this->getConnection();
		const auto factory = std::make_unique<TestGetter>(connection);

		const std::string query = "SELECT `TEST_ID`FROM `assigned_tests` INNER JOIN TESTS ON TESTS.ID = TEST_ID WHERE `GROUP_ID` = ? and TESTS.OWNER_ID = ?";
		statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, group.getID());
		stat->setString(2, owner.getID());
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());

		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(factory->getTestFromID(connection,result->getString(1)));
		}
		return tests;
	}
}
