#pragma once
#include "Question.h"

namespace ExternalData
{
	class MySQL;
	class TestGetter;
}
class Test
{

public:
		Test() = default;
		explicit Test(const std::string& test_name);
		Test(const std::string& test_name, const std::string& description, bool randomize_questions,
			const std::vector<Question> questions);

		std::string getTestID() const;
		std::string getTestName() const;
		void setTestName(const std::string& test_name);
		std::vector<Question>& getQuestions();
		void setQuestions(const std::vector<Question>& questions);
		std::string getDescription() const;
		void getDescription(const std::string& description);
		bool getRandomize() const;
		void setRandomize(bool randomize_questions);


		Test(const Test& other);
		Test(Test&& other) noexcept;
		Test& operator=(const Test& other);
		Test& operator=(Test&& other) noexcept;

	private:
		std::string TestID;
		std::string TestName;
		std::string description;
		bool randomizeQuestions;
		std::vector<Question> questions;
		Test(const std::string& test_id, const std::string& test_name, const std::string& description,
			bool randomize_questions, const std::vector<Question>& questions);
		friend class ExternalData::MySQL;
		friend class ExternalData::TestGetter;

};

