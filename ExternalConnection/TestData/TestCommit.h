#pragma once
#include "Question.h"
#include "Test.h"

namespace ExternalData
{
	class MySQL;
}

class TestCommit
{
	public:
	TestCommit(const TestCommit& other);
	TestCommit(TestCommit&& other) noexcept;
	TestCommit& operator=(const TestCommit& other);
	TestCommit& operator=(TestCommit&& other) noexcept;
	std::string getID() const;
	Test getTest() const;
	std::map<std::string, std::string> getQuestionAnswer() const;
	TestCommit(const Test testRef);
	Question getCurrentQuestion() const;
	bool isLastQuestion();
	bool getNextQuestion();
	bool getPreviousQuestion();
	void setAnswerForQuestion(Answer answer);
	Answer getCurrentQuestionAnswer();
	int getCurrentQuestionAnswerIndex();
	float calculatePercentage();
	float getProgress();

	private:
		std::string ID;
		Test test;
		std::vector<Question> questionList;
		std::map<std::string, std::string> givenQuestionAnswer;
		std::vector<Question>::iterator currentQuestion;
		TestCommit(const Test& testRef, const std::map<std::string, std::string>& given_question_answer, const std::string& ID);
		friend class ExternalData::MySQL;

};

