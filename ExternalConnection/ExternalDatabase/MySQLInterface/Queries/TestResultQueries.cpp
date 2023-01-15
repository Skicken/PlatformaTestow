#include "ecpch.h"
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "ExternalDatabase/MySQLInterface/Helpers/TestGetter.h"

namespace ExternalData
{
	void MySQL::commitTestResult(TestCommit& result, std::string STUDENT_ID)
	{
		connection_shared connection = getConnection();

		const std::string insertTestTakenQuery = "INSERT INTO `users_test_taken`(`ID`, `USER_ID`, `TEST_ID`) VALUES (?,?,?)";
		std::string testTakenID = getUniqueID();
		const statement_unique insertTestTaken(connection->prepareStatement(insertTestTakenQuery));
		insertTestTaken->setString(1, testTakenID);
		insertTestTaken->setString(2, STUDENT_ID);
		insertTestTaken->setString(3, result.getTest().getTestID());
		insertTestTaken->execute();

		const std::string insertUserAnswerQuery = "INSERT INTO `user_answer`(`TAKEN_TEST_ID`, `QUESTION_ID`, `ANSWER_ID`) VALUES (?,?,?)";
		statement_unique insertUserAnswer (connection->prepareStatement(insertUserAnswerQuery));
		for(auto questionAnswer:result.getQuestionAnswer())
		{
			insertUserAnswer->setString(1, testTakenID);
			insertUserAnswer->setString(2, questionAnswer.first);
			insertUserAnswer->setString(3, questionAnswer.second);
			insertUserAnswer->execute();
		}
	}
	std::vector<TestCommit> MySQL::getTestResults(std::string STUDENT_ID)
	{
		connection_shared connection = getConnection();
		const std::string getTestResultQuery = "SELECT `ID`, `USER_ID`, `TEST_ID` FROM `users_test_taken`";
		statement_unique getTestResult(connection->prepareStatement(getTestResultQuery));
		result_shared testResult(getTestResult->executeQuery());

		TestGetter testFactory(connection);
		std::vector<TestCommit> results;
		while(testResult->next())
		{
			std::string testID = testResult->getString(1);
			const std::string getTestQuery = "SELECT `ID`, `name`, `description`,`randomize` FROM `tests` WHERE `ID` = ?";
			statement_unique getTest(connection->prepareStatement(getTestQuery));
			getTest->setString(1, testResult->getString(3));
			result_shared getTesto(getTest->executeQuery());
			if (getTesto->next());
			Test test = testFactory.getTestFromRow(getTesto);


			std::map<std::string, std::string> givenQuestionAnswer;

			std::string getGivenQuestionAnswerQuery = "SELECT `QUESTION_ID`, `ANSWER_ID` FROM `user_answer` WHERE `TAKEN_TEST_ID` = ?";
			statement_unique getGivenQuestionAnswer(connection->prepareStatement(getGivenQuestionAnswerQuery));
			getGivenQuestionAnswer->setString(1, testID);
			result_shared questionAnswerResult(getGivenQuestionAnswer->executeQuery());
			while(questionAnswerResult->next())
			{
				givenQuestionAnswer[questionAnswerResult->getString(1)] = questionAnswerResult->getString(2);
			}
			results.push_back(TestCommit(test, givenQuestionAnswer, testID));
		}
		return results;
	}
	void MySQL::deleteTestResult(TestCommit& result)
	{
		connection_shared connection = getConnection();
		const std::string deleteTestResultQuery = "DELETE FROM `users_test_taken` WHERE `ID` = ?";
		statement_unique deleteTestResult(connection->prepareStatement(deleteTestResultQuery));
		deleteTestResult->setString(1, result.getID());
		deleteTestResult->execute();


	}

	
}
