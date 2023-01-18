#include "ptpch.h"
#include "System.h"

System* System::instance;
MainMenu* System::menu;
System::System()
{
    initVariables();
}

System::~System()
{
    CloseWindow();
    delete menu;
}
void System::update()
{
    assert(currentView != nullptr);
    this->currentView->update();
    isRun = !WindowShouldClose();

}
void System::render()
{
    assert(currentView != nullptr);

    BeginDrawing();
        ClearBackground(RAYWHITE);

    this->currentView->render();


    EndDrawing();
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
    this->setView(new LoginView());
    //Init raylib 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    
    InitWindow(GetScreenWidth(), GetScreenWidth(), appName.c_str());
    SetTargetFPS(30);
}

bool System::LoginUser(std::string username, std::string password)
{
    this->user = dataInterface->getUser(username,password);
    if (this->user != nullptr)
    {
       this->menu = getMainMenu();
    }
    return this->user != nullptr;
}

bool System::LogoutUser()
{
    delete menu;
    this->user = nullptr;
    return true;
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

MainMenu* System::getMainMenu()
{
    switch (this->user->getType())
    {
        case UserType::STUDENT:
        case UserType::TEACHER:
        case UserType::ADMIN:
            break;

    }
    return new StudentMenu();
}
