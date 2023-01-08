#include "ecpch.h"
#include "Sender.h"

User Sender::getUser() const
{
	return user;
}

std::string Sender::getEmailLogin() const
{
	return emailLogin;
}

std::string Sender::getEmailPassword() const
{
	return emailPassword;
}

Sender::Sender(const User& user, const std::string& email_login, const std::string& email_password): user(user),
                                                                                                     emailLogin(email_login),
                                                                                                     emailPassword(email_password)
{
}
