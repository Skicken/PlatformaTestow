#pragma once
#include "Question.h"
enum class Grade {};
class Test
{
	int TestID;
	std::string TestName;
	std::vector<Question> questions;
};

