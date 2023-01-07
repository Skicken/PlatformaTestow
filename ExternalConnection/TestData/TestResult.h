#pragma once
#include "Question.h"
#include "Test.h"

class TestResult
{
public:
		std::string getID() const;
		Test getTest() const;
		std::map<std::string, std::string> getQuestionAnswer() const;
		TestResult(const Test& testRef);

		TestResult(const Test& testRef, const std::map<std::string, std::string>& given_question_answer, const std::string& ID);
		Question getCurrentQuestion() const;
		bool getNextQuestion();
		void setAnswerForQuestion(Answer& answer);
	private:
		std::string ID;
		Test test;
		std::vector<Question> questionList;
		std::map<std::string, std::string> givenQuestionAnswer;
		std::vector<Question>::iterator currentQuestion;

};

