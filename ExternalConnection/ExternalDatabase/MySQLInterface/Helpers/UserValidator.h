#pragma once
#include "users/user.h"

class UserValidator
{
	public:
		static std::string validateUser(User& user, std::string login, std::string password);
};

