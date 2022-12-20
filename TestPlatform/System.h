#pragma once

#include <Views/View.h>
#include <Views/LoginView.h>

#include <users/user.h>
#include <Data/SQL.h>
#include <Mail/MailManager.h>

class System
{

	static System* instance;
	User* user;
	View* currentView;
	DataInterface* dataInterface;

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
	static User* const getLoggedUser();
	static DataInterface* const getDataInterface();
};

