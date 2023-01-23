#include "ptpch.h"
#include "System.h"

#include "Views/TeacherView/TeacherView.h"

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
    currentView.release();
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
    LoginUser("user", "user");
}

void System::LoginUser(std::string username, std::string password)
{
    this->user = dataInterface->getUser(username,password);
    if (this->user == nullptr)
    {
        INFO("User not exists");
        return;
    }

    this->setMenuView();
}

bool System::LogoutUser()
{
    this->user = nullptr;
    setView(new LoginView());
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

void System::updateFullscreen()
{
    if (IsKeyReleased(KEY_F11))
    {
        ToggleFullscreen();
    }
}

void System::setMenuView()
{
    switch (user->getType())
    {
        case UserType::STUDENT:
            setView(new StudentMenu());
            break;
		case UserType::TEACHER:
            setView(new TeacherMenu());
        break;
		default:
			setView(new TeacherMenu());

    }
}
