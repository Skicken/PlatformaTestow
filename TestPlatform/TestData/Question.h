#pragma once
#include "Answer.h"
class Question
{
	const std::string QuestionID;
	std::string question;
	std::vector<Answer> answers;
	std::string studentAnswerID;
	std::string correctAnswerID;
	bool isCorrect();
};

