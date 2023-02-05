#include "ecpch.h"
#include "UserValidator.h"

std::string UserValidator::validateUser(User& user, std::string login, std::string password)
{
	if (login.size() < 4) return "Login too short";
	if (password.size() < 4) return "Password too short";
	if (user.getName().size() < 2) return "Name too short";
	if (user.getSurname().size() < 2) return "Surname too short";
	if (user.getEmail().size() < 5) return "Email too short";
	return "";
}
