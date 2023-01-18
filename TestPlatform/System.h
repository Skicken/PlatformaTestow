#pragma once

#include <Views/View.h>
#include <Views/LoginView.h>
#include "Views/StudentMenu.h"
#include "Utilities/Mouse.h"
#include "Views/QuestionView.h"
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
	static Mouse getMouseState();

	private:
	Mouse mouse;
	void initVariables();
	static System* instance;
	std::shared_ptr<User> user;
	std::unique_ptr<View> currentView;
	std::shared_ptr <ExternalData::DataInterface> dataInterface;
	bool isRun;
	const std::string appName = "Platforma do testow";
	void updateFullscreen();

};
