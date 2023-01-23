#include "ptpch.h"
#include "StudentMenu.h"
#include "../Mail.h"
#include <raygui.h>

#include "HomeworkView.h"


void StudentMenu::update()
{
	if(Button000Pressed)
	{
		System::getInstance()->setView(new TestView());
	}
	if(Button001Pressed)
	{
		System::getInstance()->setView(new HomeworkView());
	}
	if(Button002Pressed)
	{
		System::getInstance()->setView(new Mail());
	}
	if(Button003Pressed)
	{
		System::getInstance()->LogoutUser();
	}
}

void StudentMenu::render()
{
	Button000Pressed = GuiButton(layoutRecs[0], "Tests");
	Button001Pressed = GuiButton(layoutRecs[1], "Homework");
	Button002Pressed = GuiButton(layoutRecs[2], "Send Mail");
	Button003Pressed = GuiButton(layoutRecs[3], "Logout");
	DrawText("Welcome", 24, 32, 40, GREEN);
	std::string name_surname = System::getLoggedUser()->getName() + "  " + System::getLoggedUser()->getSurname();
	DrawText(name_surname.c_str(), 24, 75, 25, GRAY);
	DrawText(ExternalData::EnumToString(System::getLoggedUser()->getType()).c_str(), 24, 95, 25, GRAY);

}

StudentMenu::StudentMenu()
{
   



}