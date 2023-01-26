#include "ptpch.h"
#include "AdminView.h"
#include <raygui.h>

#include "System.h"
#include "Views/Mail.h"
#include "Views/TeacherView/AttendanceView.h"
#include "Views/TeacherView/ManageHomeworkView.h"
#include "Views/TeacherView/ManageTestsView.h"
#include "Views/TeacherView/TestResultsTeacher.h"

void AdminView::update()
{
    if (Button003Pressed)
    {
        System::getInstance()->LogoutUser();
    }
    if (Button004Pressed)
    {
        System::getInstance()->setView(new AttendanceView());

    }
    if (Button005Pressed)
    {
        System::getInstance()->setView(new Mail());
    }
    if (Button002Pressed)
    {
        System::getInstance()->setView(new TestResultsTeacher());
    }
    if (Button001Pressed)
    {
        System::getInstance()->setView(new ManageHomeworkView());
    }
    if (Button000Pressed)
    {
        System::getInstance()->setView(new ManageTestsView());
    }
}

void AdminView::render()
{
    Button000Pressed = GuiButton(layoutRecs[0], "Manage Tests");
    Button001Pressed = GuiButton(layoutRecs[1], "Manage Homeworks");
    Button002Pressed = GuiButton(layoutRecs[2], "Test Results");
    Button003Pressed = GuiButton(layoutRecs[3], "Logout");
    Button004Pressed = GuiButton(layoutRecs[4], "Attendance List");
    Button005Pressed = GuiButton(layoutRecs[5], "Send Mail");
    Button006Pressed = GuiButton(layoutRecs[6], "Manage Users");
    DrawText("Welcome", 24, 32, 40, GREEN);
    std::string name_surname = System::getLoggedUser()->getName() + "  " + System::getLoggedUser()->getSurname();
    DrawText(name_surname.c_str(), 24, 75, 25, GRAY);
    DrawText(ExternalData::EnumToString(System::getLoggedUser()->getType()).c_str(), 24, 95, 25, GRAY);
}
