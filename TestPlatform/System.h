#pragma once

#include <Views/View.h>
#include <Views/LoginView.h>

#include <users/user.h>
#include <Connection/Database.h>
#include <Connection/MailManager.h>

class System
{

	static System* instance;
	User* user;
	View* currentView;
	bool isRun;
	public:
	System();
	~System();

	void update();
	void render();

	void setView(View* view);
	void initVariables();
	bool LoginUser(std::string username, std::string password);

	bool isRunning();
	static System* getInstance();
	User* const getLoggedUser();
};

