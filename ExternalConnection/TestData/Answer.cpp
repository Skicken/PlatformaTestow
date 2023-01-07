#include "ecpch.h"
#include "Answer.h"


Answer::Answer(const std::string& id, const std::string& answer): ID(id),
                                                                  answer(answer)
{
}

Answer::Answer(const Answer& other): ID(other.ID),
                                     answer(other.answer)
{
}

Answer::Answer(Answer&& other) noexcept: ID(std::move(other.ID)),
                                         answer(std::move(other.answer))
{
}

Answer& Answer::operator=(const Answer& other)
{
	if (this == &other)
		return *this;
	ID = other.ID;
	answer = other.answer;
	return *this;
}

Answer& Answer::operator=(Answer&& other) noexcept
{
	if (this == &other)
		return *this;
	ID = std::move(other.ID);
	answer = std::move(other.answer);
	return *this;
}

Answer::Answer(const std::string& answer): answer(answer)
{
}

Answer::Answer(const char* answer):answer(answer)
{
	
}

std::string Answer::getID() const
{
	return ID;
}

std::string Answer::getAnswer() const
{
	return answer;
}