#include "ecpch.h"
#include "TestResult.h"

std::string TestResult::getID() const
{
	return ID;
}

Test TestResult::getTest() const
{
	return test;
}

std::map<std::string, std::string> TestResult::getQuestionAnswer() const
{
	return givenQuestionAnswer;
}

TestResult::TestResult(const Test& testRef) :test(testRef),questionList(test.getQuestions()),
currentQuestion(questionList.begin())
{

}



TestResult::TestResult(const Test& testRef, const std::map<std::string, std::string>& given_question_answer, const std::string& ID): ID(ID),test(testRef),
                                                                                                              questionList(test.getQuestions()), givenQuestionAnswer(given_question_answer),
                                                                                                              currentQuestion(questionList.begin())
{

}
Question TestResult::getCurrentQuestion() const
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