#pragma once

#include <Views/View.h>
#include <Views/LoginView.h>

class System
{
	static System* instance;
	//std::shared_ptr<User> user;
	std::unique_ptr<View> currentView;
	//std::shared_ptr <ExternalData::DataInterface> dataInterface;

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
	//static std::shared_ptr<User> const getLoggedUser();
	//static std::shared_ptr <ExternalData::DataInterface> const getDataInterface();
};
