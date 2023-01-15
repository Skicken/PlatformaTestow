#pragma once
#include "ExternalDatabase/MySQLInterface/SQL.h"

namespace ExternalData {
	class QuestionInserter
	{
	public:
		explicit QuestionInserter(const connection_shared& connection);
		void insertQuestions(std::string testID, std::vector<Question>& questions);
	private:
		connection_shared connection;
		void insertAnswers(std::string questionID, std::string correctAnswerName, std::vector<Answer>& answers);

	};
}
