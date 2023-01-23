#include "ptpch.h"
#include "LoginView.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
void LoginView::update()
{
	
    if(Button001Pressed)
    {
        try
        {
            System::getInstance()->LoginUser(std::string(TextBox001Text), std::string(TextBox002Text));
        }
        catch(ExternalData::DatabaseException &e)
        {
            errorMessage = e.what();
        }
        errorMessage = "Invalid login credentials";
        showIncorrect = true;
    }

}

void LoginView::render()
{
    DrawText("Test Platform", 740, 400, 40, GRAY);
    Button001Pressed = GuiButton(layoutRecs[0], "Login");
    if (GuiTextBox(layoutRecs[1], TextBox001Text, 128, TextBox001EditMode)) TextBox001EditMode = !TextBox001EditMode;
    if (GuiTextBox(layoutRecs[2], TextBox002Text, 128, TextBox002EditMode)) TextBox002EditMode = !TextBox002EditMode;
    if (TextBox001EditMode || TextBox002EditMode) showIncorrect = false;

    GuiLabel(layoutRecs[3], "Login");
    GuiLabel(layoutRecs[4], "Password");
    if(showIncorrect)
		DrawText(errorMessage.c_str(), 740, 620, 15, RED);
    
}

LoginView::LoginView():showIncorrect(false)
{
}
