#pragma once
#include "Question.h"
#include "Test.h"

class TestResult
{
	public:
		TestResult(const Test& test, const std::map<std::string, std::string>& given_question_answer);
		Question& getCurrentQuestion();
		bool getNextQuestion();
		void setAnswerForQuestion(Answer& answer);
	private:
	Test test;
	std::map<std::string, std::string> givenQuestionAnswer;
	std::vector<Question>::iterator currentQuestion;


};

