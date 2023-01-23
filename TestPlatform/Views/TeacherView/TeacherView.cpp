#include "ptpch.h"
#include "TeacherView.h"
#include <raygui.h>

#include "AttendanceView.h"
#include "TestResultsTeacher.h"
#include "Views/Mail.h"

void TeacherMenu::update()
{
   if(Button003Pressed)
   {
       System::getInstance()->LogoutUser();
   }
	if(Button004Pressed)
   {
        System::getInstance()->setView(new AttendanceView());

   }
   if (Button005Pressed)
   {
       System::getInstance()->setView(new Mail());
   }
	if(Button002Pressed)
	{
        System::getInstance()->setView(new TestResultsTeacher());
	}
}

void TeacherMenu::render()
{
    Button000Pressed = GuiButton(layoutRecs[0], "Manage Tests");
    Button001Pressed = GuiButton(layoutRecs[1], "Manage Homeworks");
    Button002Pressed = GuiButton(layoutRecs[2], "Test Results");
    Button003Pressed = GuiButton(layoutRecs[3], "Logout");
    Button004Pressed = GuiButton(layoutRecs[4], "Attendance List");
    Button005Pressed = GuiButton(layoutRecs[5], "Send Mail");

    DrawText("Welcome", 24, 32, 40, GREEN);
    std::string name_surname = System::getLoggedUser()->getName() + "  " + System::getLoggedUser()->getSurname();
    DrawText(name_surname.c_str(), 24, 75, 25, GRAY);
    DrawText(ExternalData::EnumToString(System::getLoggedUser()->getType()).c_str(), 24, 95, 25, GRAY);
}

TeacherMenu::TeacherMenu()
{


}