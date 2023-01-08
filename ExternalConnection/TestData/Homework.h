#pragma once



class Homework
{
	public:
	Homework(const std::string& id, const std::string& question);
	Homework(const std::string& question);

	std::string getID() const;
	std::string getQuestion() const;
		
	private:
		std::string ID;
		std::string Question;

};
class HomeworkCommit
{
public:

	std::string getID() const;
	std::string getQuestion() const;
	std::string getAnswer() const;
	std::string getDeliveryDate() const;
	HomeworkCommit(const std::string& id, const std::string& question, const std::string& answer,
		const std::string& deliver_date);
	HomeworkCommit(Homework& homework, const std::string& answer);

private:
	std::string ID;
	std::string Question;
	std::string Answer;
	std::string DeliverDate;
};
