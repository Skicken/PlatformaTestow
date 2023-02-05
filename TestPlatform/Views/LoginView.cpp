#include "ptpch.h"
#include "LoginView.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
void LoginView::update()
{

    if (!loginEdit && !passwordEdit && IsKeyPressed(KEY_TAB)) loginEdit = true;
    else if (loginEdit && IsKeyPressed(KEY_TAB)) {
        loginEdit = false;
        passwordEdit = true;
    }
    else if (passwordEdit && IsKeyPressed(KEY_TAB)) {
        loginEdit = true;
        passwordEdit = false;
    }

    if(loginButton || IsKeyPressed(KEY_ENTER))
    {
        try
        {
            System::getInstance()->LoginUser(std::string(loginInput), std::string(passwordInput));
        }
        catch(ExternalData::DatabaseException &e)
        {
            errorMessage = e.what();
        }
        if(errorMessage.empty())
			errorMessage = "Invalid login credentials";
        showIncorrect = true;
    }

}

void LoginView::render()
{
    DrawText("Test Platform", 740, 400, 40, GRAY);
    loginButton = GuiButton(layoutRecs[0], "Login");
    if (GuiTextBox(layoutRecs[1], loginInput, 128, loginEdit)) loginEdit = !loginEdit;
    if (GuiTextBox(layoutRecs[2], passwordInput, 128, passwordEdit)) passwordEdit = !passwordEdit;
    if (loginEdit || passwordEdit) showIncorrect = false;

    GuiLabel(layoutRecs[3], "Login");
    GuiLabel(layoutRecs[4], "Password");
    if(showIncorrect)
		DrawText(errorMessage.c_str(), 740, 620, 15, RED);
    
}

LoginView::LoginView():showIncorrect(false)
{
}
