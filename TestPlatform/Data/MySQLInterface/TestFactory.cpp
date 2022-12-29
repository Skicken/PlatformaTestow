#include "ptpch.h"
#include "TestFactory.h"
namespace ExternalData
{
	TestFactory::TestFactory(const connection_ptr& connection): connection(connection)
	{
	}
	std::vector<Test> TestFactory::getAllTests()
	{
		const std::string query = "select ID,name,description,randomize from tests";

		statement_ptr stat(connection->prepareStatement(query));
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());
		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(getTestFromRow(result));
		}
		INFO("Test size {}", tests.size());
		return tests;
	}
	std::vector<Test> TestFactory::getAssignedTests(std::string STUDENT)
	{
		const std::string query = "select tests.ID, tests.name, description, randomize from tests INNER JOIN assigned_tests on tests.ID = assigned_tests.TEST_ID INNER JOIN user_groups on user_groups.GROUP_ID = assigned_tests.GROUP_ID INNER JOIN users on user_groups.USER_ID = users.ID where users.ID = ? ";
		statement_ptr stat(connection->prepareStatement(query));
		stat->setString(1, STUDENT);
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());

		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(getTestFromRow(result));
		}
		return tests;
	}
	std::vector<Test> TestFactory::getOwnerTest(std::string OWNER_ID)
	{
		const std::string query = "select ID,name,description,randomize from tests where OWNER_ID = ?";
		statement_ptr stat(connection->prepareStatement(query));
		stat->setString(1, OWNER_ID);
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());

		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(getTestFromRow(result));
		}
		return tests;
	}

	std::vector<Question> TestFactory::getQuestions(const std::string& testID)
	{

		const std::string query = "SELECT `ID`, `name`, `type` FROM `questions` INNER JOIN tests_questions ON questions.ID = tests_questions.QUESTION_ID where tests_questions.TEST_ID = ?";
		statement_ptr stat(connection->prepareStatement(query));
		stat->setString(1, testID);
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());
		std::vector<Question> questions;
		while(result->next())
		{
			questions.push_back(getQuestionFromRow(result));
		}
		INFO("Questions size {}", questions.size());
		return questions;
	}
	std::vector<Answer> TestFactory::getAnswers(const std::string questionID)
	{
		const std::string query = "SELECT ID,name FROM `answers` inner join question_answers on answers.ID = question_answers.ANSWER_ID where question_answers.QUESTION_ID = ?";

		const statement_ptr stat(connection->prepareStatement(query));
		stat->setString(1, questionID);

		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());
		std::vector<Answer> answers;
		while (result->next())
		{
			answers.push_back(getAnswerFromRow(result));
		}
		INFO("Answers size {}", answers.size());

		return answers;

	}


	Test TestFactory::getTestFromRow(std::shared_ptr<sql::ResultSet> result)
	{
		const std::string testID = result->getString(1);
		const std::vector<Question>& questions = getQuestions(testID);
		Test test(
			testID,
			result->getString(2),
			result->getString(3),
			result->getBoolean(4),
			questions
		);
		return test;
	}
	Question TestFactory::getQuestionFromRow(std::shared_ptr<sql::ResultSet> result)
	{
		const std::string questionID = result->getString(1);
		const std::vector<Answer> answers = getAnswers(questionID);
		Question question(
			questionID, result->getString(1), answers
		);
		return question;
	}
	Answer TestFactory::getAnswerFromRow(std::shared_ptr<sql::ResultSet> result)
	{
		Answer answer(result->getString(1), result->getString(2));
		return answer;
	}
}
