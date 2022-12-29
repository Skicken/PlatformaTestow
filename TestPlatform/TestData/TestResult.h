#pragma once
#include "Question.h"
#include "Test.h"


class TestResult
{
	enum class Grade {F,E,D,C,B,A};
	Grade grade;
	Test& test;
	std::map<std::string, std::string> givenQuestionAnswer;
	std::map<std::string, std::string> correctQuestionsAnswer;
};

