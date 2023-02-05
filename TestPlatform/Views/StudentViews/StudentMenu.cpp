#include "ptpch.h"
#include "StudentMenu.h"
#include "../Mail.h"
#include <raygui.h>

#include "HomeworkView.h"


void StudentMenu::update()
{
	if(testsButton)
	{
		System::getInstance()->setView(new TestView());
	}
	if(homeworkButton)
	{
		System::getInstance()->setView(new HomeworkView());
	}
	if(sendMailButton)
	{
		System::getInstance()->setView(new Mail());
	}
	if(logoutButton)
	{
		System::getInstance()->LogoutUser();
	}
}

void StudentMenu::render()
{
	testsButton = GuiButton(layoutRecs[0], "Tests");
	homeworkButton = GuiButton(layoutRecs[1], "Homework");
	sendMailButton = GuiButton(layoutRecs[2], "Send Mail");
	logoutButton = GuiButton(layoutRecs[3], "Logout");
	DrawText("Welcome", 24, 32, 40, GREEN);
	std::string name_surname = System::getLoggedUser()->getName() + "  " + System::getLoggedUser()->getSurname();
	DrawText(name_surname.c_str(), 24, 75, 25, GRAY);
	DrawText(ExternalData::EnumToString(System::getLoggedUser()->getType()).c_str(), 24, 95, 25, GRAY);

}
StudentMenu::StudentMenu()
{
   



}