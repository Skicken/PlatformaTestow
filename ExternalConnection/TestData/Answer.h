#pragma once
class Answer
{
	public:
		std::string getID() const;
		std::string getAnswer() const;
		Answer(const std::string& id, const std::string& answer);
		Answer(const std::string& answer);
		Answer(const char* answer);
		Answer(const Answer& other);
		Answer(Answer&& other) noexcept;
		Answer& operator=(const Answer& other);
		Answer& operator=(Answer&& other) noexcept;
	private:
		std::string ID;
		std::string answer;
};

