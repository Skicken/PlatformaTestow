#include "ptpch.h"
#include "TeacherView.h"
#include <raygui.h>

#include "AttendanceView.h"
#include "ManageHomeworkView.h"
#include "ManageTestsView.h"
#include "TestResultsTeacher.h"
#include "Views/Mail.h"

void TeacherMenu::update()
{
   if(logoutButton)
   {
       System::getInstance()->LogoutUser();
   }
	if(attendanceListButton)
   {
        System::getInstance()->setView(new AttendanceView());

   }
   if (sendMailButton)
   {
       System::getInstance()->setView(new Mail());
   }
	if(testResultsButton)
	{
        System::getInstance()->setView(new TestResultsTeacher());
	}
    if(manageHomeworksButton)
    {
        System::getInstance()->setView(new ManageHomeworkView());
    }
    if(manageTestsButton)
    {
        System::getInstance()->setView(new ManageTestsView());
    }
}

void TeacherMenu::render()
{
    manageTestsButton = GuiButton(layoutRecs[0], "Manage Tests");
    manageHomeworksButton = GuiButton(layoutRecs[1], "Manage Homeworks");
    testResultsButton = GuiButton(layoutRecs[2], "Test Results");
    logoutButton = GuiButton(layoutRecs[3], "Logout");
    attendanceListButton = GuiButton(layoutRecs[4], "Attendance List");
    sendMailButton = GuiButton(layoutRecs[5], "Send Mail");

    DrawText("Welcome", 24, 32, 40, GREEN);
    std::string name_surname = System::getLoggedUser()->getName() + "  " + System::getLoggedUser()->getSurname();
    DrawText(name_surname.c_str(), 24, 75, 25, GRAY);
    DrawText(ExternalData::EnumToString(System::getLoggedUser()->getType()).c_str(), 24, 95, 25, GRAY);
}

TeacherMenu::TeacherMenu()
{


}