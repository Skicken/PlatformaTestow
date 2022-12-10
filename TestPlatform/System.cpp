#include "ptpch.h"
#include "System.h"

System* System::instance;
System::System()
{
    initVariables();
}

System::~System()
{

}
void System::update()
{
    assert(currentView != nullptr);
    this->currentView->update();

}
void System::render()
{
    assert(currentView != nullptr);
    this->currentView->render();
}

void System::setView(View* view)
{
    delete this->currentView;
    this->currentView = view;
}

void System::initVariables()
{
    this->isRun = true;
    this->instance = this;
    this->currentView = new LoginView();
}

bool System::LoginUser(std::string username, std::string password)
{
    return (username == "admin" && password == "admin");
}

bool System::isRunning()
{
    return this->isRun;
}

System* System::getInstance()
{
    return instance;
}

User* const System::getLoggedUser()
{
    return getInstance()->user;
}
