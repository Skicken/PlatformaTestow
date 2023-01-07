#include "ecpch.h"
#include "TestResult.h"

TestResult::TestResult(const Test& test, const std::map<std::string, std::string>& given_question_answer): test(test),
	givenQuestionAnswer(given_question_answer),
	currentQuestion(this->test.getQuestions().begin())
{

}
Question& TestResult::getCurrentQuestion()
{
	return *currentQuestion;
}

bool TestResult::getNextQuestion()
{
	++currentQuestion;
	return currentQuestion != test.getQuestions().end();
}
void TestResult::setAnswerForQuestion(Answer& answer)
{
	givenQuestionAnswer[(*currentQuestion).getQuestionID()] = answer.getID();
}