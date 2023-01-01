#include "ecpch.h"
#include "Question.h"



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


Question::Question(const std::string& question, const std::vector<Answer>& answers, const Answer& correct_answer): question(question),
	answers(answers),
	correctAnswer(correct_answer)
{
}

Question::Question(const std::string& question_id, const std::string& question, const std::vector<Answer>& answers,
	const Answer& correct_answer): QuestionID(question_id),
	                               question(question),
	                               answers(answers),
	                               correctAnswer(correct_answer)
{
}

Question::Question(const Question& other): QuestionID(other.QuestionID),
                                           question(other.question),
                                           answers(other.answers),
                                           correctAnswer(other.correctAnswer)
{
}

Question::Question(Question&& other) noexcept: QuestionID(std::move(other.QuestionID)),
                                               question(std::move(other.question)),
                                               answers(std::move(other.answers)),
                                               correctAnswer(std::move(other.correctAnswer))
{
}



Answer Question::getCorrectAnswer() const
{
	return correctAnswer;
}

void Question::setCorrectAnswer(const Answer& correct_answer)
{
	correctAnswer = correct_answer;
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

std::vector<Answer>& Question::getAnswers()
{
	return answers;
}

void Question::setAnswers(const std::vector<Answer>& answers)
{
	this->answers = answers;
}
