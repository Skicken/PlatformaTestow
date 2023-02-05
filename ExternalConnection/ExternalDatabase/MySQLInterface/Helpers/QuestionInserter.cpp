#include "ecpch.h"
#include "QuestionInserter.h"

#include "Utilities.h"

namespace ExternalData {
	QuestionInserter::QuestionInserter(const connection_shared& connection): connection(connection)
	{
	}

	void QuestionInserter::insertQuestions(std::string testID, std::vector<Question>& questions)
	{
		const std::string insertQuestionQuery = "INSERT INTO `questions`(`ID`, `name`) VALUES (?,?)";
		statement_unique insertQuestion(connection->prepareStatement(insertQuestionQuery));

		const std::string insertTestQuestionQuery = "INSERT INTO `tests_questions`(`QUESTION_ID`, `TEST_ID`) VALUES (?,?)";
		statement_unique insertTestQuestion(connection->prepareStatement(insertTestQuestionQuery));

		for (auto& question : questions)
		{

			const std::string questionID = Utilities::generateID(connection);
			insertQuestion->setString(1, questionID);
			insertQuestion->setString(2, question.getQuestionName());
			insertQuestion->execute();

			insertAnswers(questionID, question.getCorrectAnswer().getAnswer(), question.getAnswers());

			insertTestQuestion->setString(1, questionID);
			insertTestQuestion->setString(2, testID);
			insertTestQuestion->execute();

		}
	}
	void QuestionInserter::insertAnswers(std::string questionID, std::string correctAnswerName, std::vector<Answer>& answers)
	{
		const std::string getAnswerIDQuery = "select ID from answers where name = ?";
		statement_unique getAnswerID(connection->prepareStatement(getAnswerIDQuery));

		const std::string insertAnswerQuery = "INSERT INTO `answers`(`ID`, `name`) VALUES (?,?)";
		statement_unique insertAnswer(connection->prepareStatement(insertAnswerQuery));

		const std::string insertQuestionAnswerQuery = "INSERT IGNORE INTO `question_answers`(`QUESTION_ID`, `ANSWER_ID`) VALUES (?,?)";
		statement_unique insertQuestionAnswer(connection->prepareStatement(insertQuestionAnswerQuery));

		const std::string correctAnswerQuery = "INSERT IGNORE INTO `correct_question_answer`(`QUESTION_ID`, `ANSWER_ID`) VALUES (?,?)";
		statement_unique correctAnswer(connection->prepareStatement(correctAnswerQuery));

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
				AnswerID = Utilities::generateID(connection);
				insertAnswer->setString(1, AnswerID);
				insertAnswer->setString(2, answer.getAnswer());
				insertAnswer->execute();
			}
			insertQuestionAnswer->setString(1, questionID);
			insertQuestionAnswer->setString(2, AnswerID);
			insertQuestionAnswer->execute();

			if (correctAnswerName == answer.getAnswer())
			{
				correctAnswer->setString(1, questionID);
				correctAnswer->setString(2, AnswerID);
				correctAnswer->execute();
			}
		}


	}
}
