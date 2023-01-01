#include "ecpch.h"
#include "TestFactory.h"

namespace ExternalData
{
	TestFactory::TestFactory(const connection_shared& connection): connection(connection)
	{
	}
	std::vector<Test> TestFactory::getAllTests()
	{
		const std::string query = "select ID,name,description,randomize from tests";

		statement_unique stat(connection->prepareStatement(query));
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());
		std::vector<Test> tests;
		while (result->next())
		{
			tests.push_back(getTestFromRow(result));
		}
		return tests;
	}
	std::vector<Test> TestFactory::getAssignedTests(std::string STUDENT)
	{
		const std::string query = "select tests.ID, tests.name, description, randomize from tests INNER JOIN assigned_tests on tests.ID = assigned_tests.TEST_ID INNER JOIN user_groups on user_groups.GROUP_ID = assigned_tests.GROUP_ID INNER JOIN users on user_groups.USER_ID = users.ID where users.ID = ? ";
		statement_unique stat(connection->prepareStatement(query));
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
		statement_unique stat(connection->prepareStatement(query));
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
		statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, testID);
		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());
		std::vector<Question> questions;
		while(result->next())
		{
			questions.push_back(getQuestionFromRow(result));
		}
		return questions;
	}
	std::vector<Answer> TestFactory::getAnswers(const std::string questionID)
	{
		const std::string query = "SELECT ID,name FROM `answers` inner join question_answers on answers.ID = question_answers.ANSWER_ID where question_answers.QUESTION_ID = ?";
		const statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, questionID);

		std::shared_ptr<sql::ResultSet> result(stat->executeQuery());
		std::vector<Answer> answers;
		while (result->next())
		{
			answers.push_back(getAnswerFromRow(result));
		}
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
		const std::string correctAnswerQuery = "SELECT ID,name FROM `answers` inner join correct_question_answer on answers.ID = correct_question_answer.ANSWER_ID where correct_question_answer.QUESTION_ID = ?";
		statement_unique correctAnswer(connection->prepareStatement(correctAnswerQuery));
		correctAnswer->setString(1, questionID);
		result_shared resultAnswer(correctAnswer->executeQuery());
		resultAnswer->next();
		Answer correct = getAnswerFromRow(resultAnswer);
	
		const std::vector<Answer> answers = getAnswers(questionID);
		Question question(
			questionID, result->getString(2), answers,correct
		);
		return question;
	}
	Answer TestFactory::getAnswerFromRow(std::shared_ptr<sql::ResultSet> result)
	{
		Answer answer(result->getString(1), result->getString(2));
		return answer;
	}
	void TestFactory::insertQuestions(std::string testID, std::vector<Question>& questions)
	{
		const std::string getQuestionIDQuery = "select ID from questions where name = ?";
		statement_unique getQuestionID(connection->prepareStatement(getQuestionIDQuery));

		const std::string insertQuestionQuery = "INSERT INTO `questions`(`ID`, `name`) VALUES (UNHEX(REPLACE(UUID(), '-', '')),?)";
		statement_unique insertQuestion(connection->prepareStatement(insertQuestionQuery));

		const std::string insertTestQuestionQuery = "INSERT INTO `tests_questions`(`QUESTION_ID`, `TEST_ID`) VALUES (?,?)";
		statement_unique insertTestQuestion(connection->prepareStatement(insertTestQuestionQuery));

		for (auto& question : questions)
		{
			getQuestionID->setString(1, question.getQuestionName());
			result_unique result(getQuestionID->executeQuery());
			std::string questionID;
			if (result->next())
			{
				questionID = result->getString(1);
			}
			else
			{
				insertQuestion->setString(1, question.getQuestionName());
				insertQuestion->execute();
				getQuestionID->setString(1, question.getQuestionName());
				result_unique re_result(getQuestionID->executeQuery());
				if (!re_result->next()) throw sql::SQLException("could not fetch question ID");

				questionID = re_result->getString(1);
			}
			insertAnswers(questionID,question.getCorrectAnswer().getAnswer(), question.getAnswers());

			insertTestQuestion->setString(1, questionID);
			insertTestQuestion->setString(2, testID);
			insertTestQuestion->execute();


		}
	}
	void TestFactory::insertAnswers(std::string questionID, std::string correctAnswerName, std::vector<Answer>& answers)
	{
		const std::string getAnswerIDQuery = "select ID from answers where name = ?";
		statement_unique getAnswerID(connection->prepareStatement(getAnswerIDQuery));

		const std::string insertAnswerQuery = "INSERT INTO `answers`(`ID`, `name`) VALUES (UNHEX(REPLACE(UUID(), '-', '')),?)";
		statement_unique insertAnswer(connection->prepareStatement(insertAnswerQuery));

		const std::string insertQuestionAnswerQuery = "INSERT IGNORE INTO `question_answers`(`QUESTION_ID`, `ANSWER_ID`) VALUES (?,?)";
		statement_unique insertQuestionAnswer(connection->prepareStatement(insertQuestionAnswerQuery));

		for (auto& answer : answers)
		{
			getAnswerID->setString(1, answer.getAnswer());
			result_unique result(getAnswerID->executeQuery());
			std::string AnswerID;
			if (result->next())
			{
				AnswerID = result->getString(1);
			}
			else
			{
				insertAnswer->setString(1, answer.getAnswer());
				insertAnswer->execute();
				getAnswerID->setString(1, answer.getAnswer());

				result_unique re_result(getAnswerID->executeQuery());
				if (!re_result->next()) throw sql::SQLException("could not fetch answer ID");
				AnswerID = re_result->getString(1);
			}
			insertQuestionAnswer->setString(1, questionID);
			insertQuestionAnswer->setString(2, AnswerID);
			insertQuestionAnswer->execute();
		}
		getAnswerID->setString(1, correctAnswerName);
		result_unique result(getAnswerID->executeQuery());
		if(!result->next()) throw sql::SQLException("could not fetch correct answer ID");
		const std::string correctAnswerID = result->getString(1);

		std::string correctAnswerQuery = "INSERT IGNORE INTO `correct_question_answer`(`QUESTION_ID`, `ANSWER_ID`) VALUES (?,?)";
		statement_unique correctAnswer(connection->prepareStatement(correctAnswerQuery));
		correctAnswer->setString(1, questionID);
		correctAnswer->setString(2, correctAnswerID);
		correctAnswer->execute();
	}
}
