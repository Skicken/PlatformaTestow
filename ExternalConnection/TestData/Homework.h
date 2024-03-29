#pragma once
#include "users/user.h"


namespace ExternalData
{
	class MySQL;
}

class Homework
{
	public:
	Homework(const std::string& question);

	std::string getID() const;
	std::string getQuestion() const;
		
	private:
		Homework(const std::string& id, const std::string& question);
		std::string ID;
		std::string Question;
		friend class ExternalData::MySQL;

};
class HomeworkCommit
{
	public:
	User getUser() const;
	std::string getID() const;
	std::string getQuestion() const;
	std::string getAnswer() const;
	std::string getDeliveryDate() const;
	HomeworkCommit(Homework& homework, const std::string& answer);

	private:
		std::string ID;
		std::string Question;
		std::string Answer;
		std::string DeliverDate;
		User user;
		HomeworkCommit(const std::string& id, const std::string& question, const std::string& answer,
			const std::string& deliver_date, const User& user);
		friend class ExternalData::MySQL;

};
