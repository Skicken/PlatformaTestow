#include "ecpch.h"
#include "TestCommit.h"


TestCommit::TestCommit(const TestCommit& other): ID(other.ID),
                                                 test(other.test),
                                                 questionList(other.questionList),
                                                 givenQuestionAnswer(other.givenQuestionAnswer),
                                                 currentQuestion(questionList.begin())
{

}

TestCommit::TestCommit(TestCommit&& other) noexcept: ID(std::move(other.ID)),
                                                     test(std::move(other.test)),
                                                     questionList(std::move(other.questionList)),
                                                     givenQuestionAnswer(std::move(other.givenQuestionAnswer)),
                                                     currentQuestion(questionList.begin())
{
}

TestCommit& TestCommit::operator=(const TestCommit& other)
{
	if (this == &other)
		return *this;
	ID = other.ID;
	test = other.test;
	questionList = other.questionList;
	givenQuestionAnswer = other.givenQuestionAnswer;
	currentQuestion = questionList.begin();
	return *this;
}

TestCommit& TestCommit::operator=(TestCommit&& other) noexcept
{
	if (this == &other)
		return *this;
	ID = std::move(other.ID);
	test = std::move(other.test);
	questionList = std::move(other.questionList);
	givenQuestionAnswer = std::move(other.givenQuestionAnswer);
	currentQuestion = questionList.begin();
	return *this;
}

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

bool TestCommit::isLastQuestion()
{
	return currentQuestion == questionList.end();
}

bool TestCommit::getNextQuestion()
{
	if(currentQuestion!= questionList.end())
		++currentQuestion;
	return currentQuestion != questionList.end();
}

bool TestCommit::getPreviousQuestion()
{
	if (currentQuestion != questionList.begin())
		--currentQuestion;
	return currentQuestion != questionList.begin();
}

void TestCommit::setAnswerForQuestion(Answer answer)
{
	givenQuestionAnswer[getCurrentQuestion().getQuestionID()] = answer.getID();
}

Answer TestCommit::getCurrentQuestionAnswer()
{
	for (auto& answer : currentQuestion->getAnswers())
	{
		if (answer.getID() == givenQuestionAnswer[getCurrentQuestion().getQuestionID()])
			return answer;
	}
	return Answer("");
}

int TestCommit::getCurrentQuestionAnswerIndex()
{
	int i = 0;
	for (auto& answer : currentQuestion->getAnswers())
	{
		if (answer.getID() == givenQuestionAnswer[getCurrentQuestion().getQuestionID()])
			return i;
		i++;
	}
	return 0;
}


float TestCommit::calculatePercentage()
{
	assert(questionList.size() > 0);
	int score = 0;
	for(auto &question:questionList)
	{
		if(question.getCorrectAnswer().getID() == givenQuestionAnswer[question.getQuestionID()])
		{
			++score;
		}
	}
	float size = questionList.size();
	return static_cast<float>(score) * 100 / size;
}

float TestCommit::getProgress()
{
	const float index = currentQuestion - questionList.begin() + 1;
	const float size = questionList.size();
	return index/size;
}
