#include "ptpch.h"
#include "Test.h"

std::string Test::getDescription() const
{
	return description;
}

void Test::getDescription(const std::string& description)
{
	this->description = description;
}

Test::Test(const Test& other): TestID(other.TestID),
                               TestName(other.TestName),
                               description(other.description),
                               randomizeQuestions(other.randomizeQuestions),
                               questions(other.questions)
{
}

Test::Test(Test&& other) noexcept: TestID(std::move(other.TestID)),
                                   TestName(std::move(other.TestName)),
                                   description(std::move(other.description)),
                                   randomizeQuestions(other.randomizeQuestions),
                                   questions(std::move(other.questions))
{
}

Test& Test::operator=(const Test& other)
{
	if (this == &other)
		return *this;
	TestID = other.TestID;
	TestName = other.TestName;
	description = other.description;
	randomizeQuestions = other.randomizeQuestions;
	questions = other.questions;
	return *this;
}

Test& Test::operator=(Test&& other) noexcept
{
	if (this == &other)
		return *this;
	TestID = std::move(other.TestID);
	TestName = std::move(other.TestName);
	description = std::move(other.description);
	randomizeQuestions = other.randomizeQuestions;
	questions = std::move(other.questions);
	return *this;
}

bool Test::getRandomize() const
{
	return randomizeQuestions;
}

void Test::setRandomize(bool randomize_questions)
{
	randomizeQuestions = randomize_questions;
}

Test::Test(const std::string& test_id, const std::string& test_name, const std::string& description,
           bool randomize_questions, const std::vector<Question>& questions): TestID(test_id),
                                                                              TestName(test_name),
                                                                              description(description),
                                                                              randomizeQuestions(randomize_questions),
                                                                              questions(questions)
{
}

std::string Test::getTestID() const
{
	return TestID;
}

std::string Test::getTestName() const
{
	return TestName;
}

void Test::setTestName(const std::string& test_name)
{
	TestName = test_name;
}

std::vector<Question> Test::getQuestions() const
{
	return questions;
}

void Test::setQuestions(const std::vector<Question>& questions)
{
	this->questions = questions;
}
