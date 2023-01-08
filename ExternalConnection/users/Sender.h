#pragma once
#include "user.h"

class Sender
{
	public:
	User getUser() const;
	std::string getEmailLogin() const;
	std::string getEmailPassword() const;

	Sender(const User& user, const std::string& email_login, const std::string& email_password);

	private:
		User user;
		std::string emailLogin;
		std::string emailPassword;
};

