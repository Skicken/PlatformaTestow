#include "ptpch.h"
#include "LoginView.h"

void LoginView::update()
{
    Mouse mouse = System::getMouseState();
    if (loginButton.Click(mouse))
    {
        INFO("Input login: {}",login.StringReturn());
        INFO("Input password: {}", password.StringReturn())
        System::getInstance()->LoginUser(login.StringReturn(), password.StringReturn());
        showIncorrect = true;
    }
    login.Write(mouse);
    password.Write(mouse);

}

void LoginView::render()
{
    DrawRectangle(700, 500, 520, 50, WHITE);
    DrawRectangle(700, 610, 520, 50, WHITE);
    loginButton.DrawButton();
    loginInfoText.DrawText();
    login.DrawText();
    password.DrawText();
    if(showIncorrect)
        incorrect.DrawText();
    
}

LoginView::LoginView()
{
    loginButton.Edit(860, 800, 200, 60);
    loginInfoText.Edit(875, 815, 215, 100, 30, "Zaloguj sie");
    login.Edit(710, 510, 440, 60, 30, "Login");
    password.Edit(710, 620, 440, 60, 30, "Haslo");
    incorrect.Edit(860, 700, 200, 60,20, "Nieprawidlowe dane");
    incorrect.setColor(RED);
}
