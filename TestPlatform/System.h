#pragma once

#include <Views/View.h>
#include <Views/LoginView.h>
#include <MainMenus/StudentMenu.h>
#include <MainMenus/MainMenu.h>

class System
{
	public:
	System();
	~System();

	void update();
	void render();

	void setView(View* view);
	void initVariables();
	bool LoginUser(std::string username, std::string password);
	bool LogoutUser();
	bool isRunning();

	static System* getInstance();
	static std::shared_ptr<User> const getLoggedUser();
	static std::shared_ptr <ExternalData::DataInterface> const getDataInterface();

	private:
	static System* instance;
	std::shared_ptr<User> user;
	std::unique_ptr<View> currentView;
	std::shared_ptr <ExternalData::DataInterface> dataInterface;
	static MainMenu* menu;
	MainMenu* getMainMenu();
	bool isRun;
	const std::string appName = "Platforma do testow";
};
