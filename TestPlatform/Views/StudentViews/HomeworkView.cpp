#include "ptpch.h"
#include "HomeworkView.h"
#include "raygui.h"
#include "System.h"

HomeworkView::HomeworkView()
{
    refreshData();
}

void HomeworkView::update()
{
    if (Button002Pressed)
    {
        System::getInstance()->setMenuView();
    }
    if(Button003Pressed && ListView000Active>= 0 && ListView000Active< homeworks.size())
    {
        HomeworkCommit commit(homeworks[ListView000Active], homeworkText);
        System::getDataInterface()->commitHomework(System::getLoggedUser()->getID(),commit);
        refreshData();
    }
}

void HomeworkView::render()
{
    ListView000Active = GuiListView(layoutRecs[0], Helper::ListToStringSeparated(homeworks,&Homework::getQuestion
    ).c_str(), &ListView000ScrollIndex, ListView000Active);
    Button002Pressed = GuiButton(layoutRecs[1], "Menu");
    if (GuiTextBoxMulti(layoutRecs[2],  homeworkText, 256,  homeworkEditMode))  homeworkEditMode = ! homeworkEditMode;
    Button003Pressed = GuiButton(layoutRecs[3], "Send Homework");
}

void HomeworkView::refreshData()
{

    homeworks = System::getDataInterface()->getAllAvailableHomework(
        System::getLoggedUser()->getID()
    );
    INFO("Loaded {} homeworks", homeworks.size())
}
