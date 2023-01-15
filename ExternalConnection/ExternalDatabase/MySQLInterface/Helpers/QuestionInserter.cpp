#include "ecpch.h"
#include "QuestionInserter.h"
namespace ExternalData {
	QuestionInserter::QuestionInserter(const connection_shared& connection): connection(connection)
	{
	}

	void QuestionInserter::insertQuestions(std::string testID, std::vector<Question>& questions)
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
		if (!result->next()) throw sql::SQLException("could not fetch correct answer ID");
		const std::string correctAnswerID = result->getString(1);

		std::string correctAnswerQuery = "INSERT IGNORE INTO `correct_question_answer`(`QUESTION_ID`, `ANSWER_ID`) VALUES (?,?)";
		statement_unique correctAnswer(connection->prepareStatement(correctAnswerQuery));
		correctAnswer->setString(1, questionID);
		correctAnswer->setString(2, correctAnswerID);
		correctAnswer->execute();
	}
}