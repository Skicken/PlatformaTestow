#include "ptpch.h"
#include "Question.h"

Question::Question(const std::string& question_id, const std::string& question, const std::vector<Answer>& answers): QuestionID(question_id),
	question(question),
	answers(answers)
{
}

Question::Question(const Question& other): QuestionID(other.QuestionID),
                                           question(other.question),
                                           answers(other.answers)
{
}

Question::Question(Question&& other) noexcept: QuestionID(std::move(other.QuestionID)),
                                               question(std::move(other.question)),
                                               answers(std::move(other.answers))
{
}

Question& Question::operator=(const Question& other)
{
	if (this == &other)
		return *this;
	QuestionID = other.QuestionID;
	question = other.question;
	answers = other.answers;
	return *this;
}

Question& Question::operator=(Question&& other) noexcept
{
	if (this == &other)
		return *this;
	QuestionID = std::move(other.QuestionID);
	question = std::move(other.question);
	answers = std::move(other.answers);
	return *this;
}

Question::Question(const std::string& question_id, const std::string& question): QuestionID(question_id),
                                                                                 question(question)
{
}
std::string Question::getQuestionID() const
{
	return QuestionID;
}

std::string Question::getQuestionName() const
{
	return question;
}

void Question::setQuestion(const std::string& question)
{
	this->question = question;
}

std::vector<Answer> Question::getAnswers() const
{
	return answers;
}

void Question::setAnswers(const std::vector<Answer>& answers)
{
	this->answers = answers;
}
