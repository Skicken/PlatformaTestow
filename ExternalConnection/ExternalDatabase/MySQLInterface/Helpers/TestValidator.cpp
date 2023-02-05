#include "ecpch.h"
#include "TestValidator.h"

std::string  TestValidator::validTest(Test& test)
{
	if (test.getTestName().empty()) return "test name not set";
	if (test.getQuestions().empty()) return "questions set is empty";
	for(auto &question : test.getQuestions())
	{
		if (question.getAnswers().empty()) return "answers are not set in  "+question.getQuestionName();
		if (question.getCorrectAnswer().getAnswer().empty()) return "correct answer not set";
		bool correctAnswerIS = false;
		for(auto &answer: question.getAnswers())
		{
			if (question.getCorrectAnswer().getAnswer() == answer.getAnswer())correctAnswerIS = true;
		}
		if (!correctAnswerIS) return "correct answers is not contained in answers";
	}
	return "";
}
