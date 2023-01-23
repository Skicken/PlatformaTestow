#pragma once

#include <Views/View.h>
#include <Views/LoginView.h>
#include "Views/StudentViews/StudentMenu.h"
class System
{
	public:
	System();
	~System();

	void update();
	void render();

	void setMenuView();
	void setView(View* view);
	void LoginUser(std::string username, std::string password);
	bool LogoutUser();
	bool isRunning();

	static System* getInstance();
	static std::shared_ptr<User> const getLoggedUser();
	static std::shared_ptr <ExternalData::DataInterface> const getDataInterface();

	private:
	void initVariables();
	static System* instance;
	std::shared_ptr<User> user;
	std::unique_ptr<View> currentView;
	std::shared_ptr <ExternalData::DataInterface> dataInterface;
	bool isRun;
	const std::string appName = "Platforma do testow";
	void updateFullscreen();

};
