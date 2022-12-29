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
    this->currentView = std::unique_ptr<View>{ view };
}

void System::initVariables()
{
    this->isRun = true;
    this->instance = this;
    this->currentView = std::make_unique<LoginView>();
    this->dataInterface = std::make_unique<ExternalData::MySQL>();
}

bool System::LoginUser(std::string username, std::string password)
{
    this->user = std::unique_ptr<User>{ dataInterface->getUser(username,password) };
    return this->user != nullptr;
}

bool System::isRunning()
{
    return this->isRun;
}

System* System::getInstance()
{
    return instance;
}

std::shared_ptr<User> const System::getLoggedUser()
{
    return getInstance()->user;
}

std::shared_ptr <ExternalData::DataInterface> const System::getDataInterface()
{
    return getInstance()->dataInterface;
}
