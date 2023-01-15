#include "ecpch.h"
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "ExternalDatabase/MySQLInterface/Helpers/TestGetter.h"
#include "ExternalDatabase/MySQLInterface/Helpers/QuestionInserter.h"

namespace ExternalData
{

	void MySQL::modifyTest(Test& test, std::string OWNER_ID)
	{
		deleteTest(test);
		addTest(test,OWNER_ID);
	}
	void MySQL::deleteTest(Test& test)
	{
		const connection_shared connection = getConnection();
		const std::string deleteQuestionAnswerQuery= "DELETE FROM `question_answers` WHERE `QUESTION_ID` = ?";
		statement_unique deleteQuestionAnswer(connection->prepareStatement(deleteQuestionAnswerQuery));

		const std::string deleteCorrectAnswerQuery = "DELETE FROM `correct_question_answer` WHERE `QUESTION_ID` = ?";
		statement_unique deleteCorrectAnswer(connection->prepareStatement(deleteCorrectAnswerQuery));

		const std::string deleteTestQuery = "DELETE FROM `tests` WHERE `ID` = ?";
		statement_unique deleteTest(connection->prepareStatement(deleteTestQuery));

		for(auto &question:test.getQuestions())
		{
			deleteCorrectAnswer->setString(1, question.getQuestionID());
			deleteCorrectAnswer->execute();

			deleteQuestionAnswer->setString(1, question.getQuestionID());
			deleteQuestionAnswer->execute();

		}
		deleteTest->setString(1, test.getTestID());
		deleteTest->execute();

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

		const auto  inserter = std::make_unique<QuestionInserter>(connection);
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
}
