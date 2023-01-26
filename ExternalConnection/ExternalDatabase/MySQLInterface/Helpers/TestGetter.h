#pragma once
#include "SQL.h"
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "TestData/Test.h"
namespace ExternalData
{
	class TestGetter
	{
	public:
		explicit TestGetter(const connection_shared& connection);

		private:
		connection_shared connection;
		std::vector<Question> getQuestions(const std::string& testID);
		std::vector<Answer> getAnswers(const std::string questionID);
		Question getQuestionFromRow(std::shared_ptr<sql::ResultSet> result);
		Answer getAnswerFromRow(std::shared_ptr<sql::ResultSet> result);

		public:
		Test getTestFromRow(std::shared_ptr<sql::ResultSet> result);
		Test getTestFromID(connection_shared connection,std::string ID);


	};
}