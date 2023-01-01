#include "ecpch.h"
#include "Data/MySQLInterface/SQL.h"
#include "Data/MySQLInterface/Helpers/TestFactory.h"

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
	//no test should exist with the same name
	void MySQL::addTest(Test& test, std::string OWNER_ID)
	{
		connection_shared connection = getConnection();

		const std::string query = "INSERT INTO `tests`(`ID`, `OWNER_ID`, `name`, `randomize`, `description`) VALUES (UNHEX(REPLACE(UUID(), '-', '')),?,?,?,?)";
		statement_unique testQuery(connection->prepareStatement(query));

		testQuery->setString(1, OWNER_ID);
		testQuery->setString(2, test.getTestName());
		testQuery->setBoolean(3, test.getRandomize());
		testQuery->setString(4, test.getDescription());
		testQuery->execute();
		
		const std::string getIDquery = "select ID from tests where name = ?";
		statement_unique getID (connection->prepareStatement(getIDquery));

		getID->setString(1, test.getTestName());
		
		result_unique result(getID->executeQuery());
		if (!result->next()) throw sql::SQLException("could not fetch test ID");
		std::string testID = result->getString(1);

		const auto  factory = std::make_unique<TestFactory>(connection);
		factory->insertQuestions(testID, test.getQuestions());

	}
	std::vector<Test> MySQL::getAllTests()
	{
		connection_shared connection = this->getConnection();
		const auto  factory = std::make_unique<TestFactory>(connection);
		return factory->getAllTests();

	}
	std::vector<Test> MySQL::getStudentAvailableTest(std::string STUDENT_ID)
	{
		connection_shared connection = this->getConnection();
		const auto factory = std::make_unique<TestFactory>(connection);
		return factory->getAssignedTests(STUDENT_ID);

	}
	std::vector<Test> MySQL::getTeacherTests(std::string OWNER_ID)
	{
		connection_shared connection = this->getConnection();
		const auto factory = std::make_unique<TestFactory>(connection);
		return factory->getOwnerTest(OWNER_ID);
	}
}
