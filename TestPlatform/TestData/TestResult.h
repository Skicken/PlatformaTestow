#pragma once
#include "Question.h"

class TestResult
{
	enum class Grade {F,E,D,C,B,A};
	Grade grade;
	std::vector<Question> givenQuestionAnswers;
	double caluclatePercentage();
};

