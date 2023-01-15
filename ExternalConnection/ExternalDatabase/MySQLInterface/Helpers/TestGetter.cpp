#include "ecpch.h"
#include "TestGetter.h"

namespace ExternalData
{
	TestGetter::TestGetter(const connection_shared& connection): connection(connection)
	{
	}

	std::vector<Question> TestGetter::getQuestions(const std::string& testID)
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
	std::vector<Answer> TestGetter::getAnswers(const std::string questionID)
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
	Test TestGetter::getTestFromRow(std::shared_ptr<sql::ResultSet> result)
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
	Question TestGetter::getQuestionFromRow(std::shared_ptr<sql::ResultSet> result)
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
	Answer TestGetter::getAnswerFromRow(std::shared_ptr<sql::ResultSet> result)
	{
		Answer answer(result->getString(1), result->getString(2));
		return answer;
	}

}
