#include "ecpch.h"
#include "Homework.h"


HomeworkCommit::HomeworkCommit(const std::string& id, const std::string& question, const std::string& answer,
	const std::string& deliver_date, const User& user): ID(id),
	                                                    Question(question),
	                                                    Answer(answer),
	                                                    DeliverDate(deliver_date),
	                                                    user(user)
{
}

User HomeworkCommit::getUser() const
{
	return user;
}

std::string HomeworkCommit::getID() const
{
	return ID;
}

std::string HomeworkCommit::getQuestion() const
{
	return Question;
}

std::string HomeworkCommit::getAnswer() const
{
	return Answer;
}

std::string HomeworkCommit::getDeliveryDate() const
{
	return DeliverDate;
}



HomeworkCommit::HomeworkCommit(Homework& homework, const std::string& answer)
{
	this->ID = homework.getID();
	this->Question = homework.getQuestion();
	this->Answer = answer;
}

Homework::Homework(const std::string& id, const std::string& question): ID(id),
                                                                        Question(question)
{
}

Homework::Homework(const std::string& question): Question(question)
{
}

std::string Homework::getID() const
{
	return ID;
}

std::string Homework::getQuestion() const
{
	return Question;
}

