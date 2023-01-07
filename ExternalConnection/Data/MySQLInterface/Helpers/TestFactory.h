#pragma once
#include "SQL.h"
#include "Data/MySQLInterface/SQL.h"
#include "TestData/Test.h"
namespace ExternalData
{
	class TestFactory
	{
	public:
		explicit TestFactory(const connection_shared& connection);

	private:
		connection_shared connection;
		public:
		std::vector<Question> getQuestions(const std::string& testID);
		std::vector<Test> getOwnerTest(std::string OWNER_ID);
		std::vector<Test> getAssignedTests(std::string STUDENT);
		std::vector<Test> getAllTests();
		std::vector<Answer> getAnswers(const std::string questionID);


		Test getTestFromRow(std::shared_ptr<sql::ResultSet> result);
		Question getQuestionFromRow(std::shared_ptr<sql::ResultSet> result);
		Answer getAnswerFromRow(std::shared_ptr<sql::ResultSet> result);

		void insertQuestions(std::string testID,std::vector<Question>& questions);
		void insertAnswers(std::string questionID,std::string correctAnswerName, std::vector<Answer>& answers);
	};
}