#include "ptpch.h"
#include "AdminView.h"
#include <raygui.h>

#include "ManageUsersView.h"
#include "System.h"
#include "Views/Mail.h"
#include "Views/TeacherView/AttendanceView.h"
#include "Views/TeacherView/ManageHomeworkView.h"
#include "Views/TeacherView/ManageTestsView.h"
#include "Views/TeacherView/TestResultsTeacher.h"

void AdminView::update()
{

	TeacherMenu::update();
	if (manageUsersButton) System::getInstance()->setView(new ManageUsersView());
	
}

void AdminView::render()
{

    TeacherMenu::render();
	manageUsersButton = GuiButton(manageUsersRect, "Manage Users");

}
