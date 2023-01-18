#include "ptpch.h"
#include "System.h"

System* System::instance;
System::System()
{
    initVariables();
}

System::~System()
{
    CloseWindow();
}
void System::update()
{
    assert(currentView != nullptr);
    this->currentView->update();
    isRun = !WindowShouldClose();

    mouse.update();
    updateFullscreen();

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
    InitWindow(GetScreenWidth(), GetScreenWidth(), appName.c_str());
    SetTargetFPS(30);
}

void System::LoginUser(std::string username, std::string password)
{
    this->user = dataInterface->getUser(username,password);
    if (this->user == nullptr) return;

    this->setMenuView();
    this->setView(new StudentMenu());
}

bool System::LogoutUser()
{
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

Mouse System::getMouseState()
{
    return instance->mouse;
}

void System::updateFullscreen()
{
    if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
    {
        int display = GetCurrentMonitor();
        if (IsWindowFullscreen())
        {
            SetWindowSize(800, 450);
        }
        else
        {
            SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        }
        ToggleFullscreen();
    }
}

void System::setMenuView()
{
    switch (user->getType())
    {
        case UserType::STUDENT:
            setView(new StudentMenu());

    }
}
