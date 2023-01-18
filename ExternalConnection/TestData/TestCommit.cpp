#include "ecpch.h"
#include "TestCommit.h"


std::string TestCommit::getID() const
{
	return ID;
}

Test TestCommit::getTest() const
{
	return test;
}

std::map<std::string, std::string> TestCommit::getQuestionAnswer() const
{
	return givenQuestionAnswer;
}

TestCommit::TestCommit(const Test testRef) :test(testRef),questionList(test.getQuestions())
{
	if (testRef.getRandomize())
	{
		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(questionList), std::end(questionList), rng);
	}
	currentQuestion = questionList.begin();
}



TestCommit::TestCommit(const Test& testRef, const std::map<std::string, std::string>& given_question_answer, const std::string& ID): ID(ID),test(testRef),
                                                                                                              questionList(test.getQuestions()), givenQuestionAnswer(given_question_answer),
                                                                                                              currentQuestion(questionList.begin())
{

}
Question TestCommit::getCurrentQuestion() const
{
	return *currentQuestion;
}

bool TestCommit::getNextQuestion()
{
	if(currentQuestion!=test.getQuestions().end())
		currentQuestion++;
	return currentQuestion == test.getQuestions().end();
}
void TestCommit::setAnswerForQuestion(Answer answer)
{
	givenQuestionAnswer[getCurrentQuestion().getQuestionID()] = answer.getID();
}

TestCommit::TestCommit(const TestCommit& other):
	test(other.test)
{
	this->ID = other.ID;
	this->currentQuestion = other.currentQuestion;
	this->givenQuestionAnswer = other.givenQuestionAnswer;
	this->test = other.test;
}

int TestCommit::calculatePercentage()
{
	int score = 0;
	for(auto question:questionList)
	{
		if(question.getCorrectAnswer().getID() == givenQuestionAnswer[question.getQuestionID()])
		{
			score++;
		}
	}
	return score * 100 / questionList.size();
}
