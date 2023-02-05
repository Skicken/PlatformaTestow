#pragma once
class SimplifiedMessage
{
	public:
	std::string getTitle() const;
	std::string getMessage() const;

	SimplifiedMessage(const std::string& title, const std::string& message);

	private:
		std::string title;
		std::string message;
};

