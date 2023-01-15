#include "ecpch.h"
#include "SimplifiedMessage.h"

std::string SimplifiedMessage::getTitle() const
{
	return title;
}

std::string SimplifiedMessage::getMessage() const
{
	return message;
}

SimplifiedMessage::SimplifiedMessage(const std::string& title, const std::string& message): title(title),
                                                                                            message(message)
{
}
