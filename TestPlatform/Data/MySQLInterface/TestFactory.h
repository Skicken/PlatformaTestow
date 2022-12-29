#pragma once
#include "SQL.h"
#include "TestData/Test.h"
namespace ExternalData
{
	class TestFactory
	{
	public:
		explicit TestFactory(const connection_ptr& connection);

	private:
		connection_ptr connection;
		public:
		std::vector<Question> getQuestions(const std::string& testID);
		std::vector<Test> getOwnerTest(std::string OWNER_ID);
		std::vector<Test> getAssignedTests(std::string STUDENT);
		std::vector<Test> getAllTests();
		std::vector<Answer> getAnswers(const std::string questionID);


		Test getTestFromRow(std::shared_ptr<sql::ResultSet> result);
		Question getQuestionFromRow(std::shared_ptr<sql::ResultSet> result);
		Answer getAnswerFromRow(std::shared_ptr<sql::ResultSet> result);
	};
}