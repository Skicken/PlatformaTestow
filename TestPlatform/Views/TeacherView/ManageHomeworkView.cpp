#include "ptpch.h"
#include "ManageHomeworkView.h"
#include <raygui.h>

#include "System.h"
#include "Utilities/ClassToStringFormatter.h"

ManageHomeworkView::ManageHomeworkView()
{
    refreshData();
}
void ManageHomeworkView::update()
{
    if (menuButton) System::getInstance()->setMenuView();
    if(deleteHomeworkButton && homeworkSelected)
    {
        System::getDataInterface()->deleteHomework(allHomeworks[selectedHomeworkIndex]);

        refreshData();
    }
    if(addHomeworkButton && groupSelected)
    {
        Homework home(homeworkNameInput);
    	System::getDataInterface()->addHomework(groups[selectedGroupIndex],home);
        refreshData();
    }
}

void ManageHomeworkView::render()
{
    if (GuiTextBox(layoutRecs[0], homeworkNameInput, 128, homeworkNameEdit)) homeworkNameEdit = !homeworkNameEdit;

    int previous = selectedGroupIndex;
    selectedGroupIndex = GuiListView(layoutRecs[8], Helper::ListToStringSeparated(groups,&Group::getName).c_str(), &ListView008ScrollIndex, selectedGroupIndex);
    groupSelected = selectedGroupIndex >= 0 && selectedGroupIndex < groups.size();
    if (groupSelected) {
        if (previous != selectedGroupIndex) allHomeworks = System::getDataInterface()->getHomeworkForGroup(groups[selectedGroupIndex].getID());
        selectedHomeworkIndex = GuiListView(layoutRecs[2], Helper::ListToStringSeparated(allHomeworks, &Homework::getQuestion).c_str(), &ListView002ScrollIndex, selectedHomeworkIndex);
        homeworkSelected = selectedHomeworkIndex >= 0 && selectedHomeworkIndex < allHomeworks.size();
    }

     previous = selectedUserIndex;
     selectedUserIndex = GuiListView(layoutRecs[5],
         Helper::ListToStringSeparated(users,ClassToStringFormatter::userToString).c_str(), &ListView005ScrollIndex, selectedUserIndex);
    userSelected = selectedUserIndex >= 0 && selectedUserIndex < users.size();
    if (userSelected)
    {
        if (previous != selectedUserIndex) commits = System::getDataInterface()->getCommitHomework(users[selectedUserIndex].getID());
        selectedHomeworkCommitIndex = GuiListView(layoutRecs[6], Helper::ListToStringSeparated(commits, ClassToStringFormatter::homeworkCommitToString).c_str(), &ListView006ScrollIndex, selectedHomeworkCommitIndex);

    }
    homeworkCommitSelected = selectedHomeworkCommitIndex >= 0 && selectedHomeworkCommitIndex < commits.size() && userSelected;

    if (homeworkCommitSelected)
    {
        std::string answerHomework = commits[selectedHomeworkCommitIndex].getAnswer();
        GuiTextBoxMulti(layoutRecs[7], const_cast<char*>(answerHomework.c_str()), 128, viewHomeworkEdit);
    }

    menuButton = GuiButton(layoutRecs[1], "Menu");
    addHomeworkButton = GuiButton(layoutRecs[3], "Add Homework");
    deleteHomeworkButton = GuiButton(layoutRecs[4], "Delete Homework");
}



void ManageHomeworkView::refreshData()
{
    groups = System::getDataInterface()->getAllGroups();
    users = System::getDataInterface()->getAllUsers();
    if(groups.size()>0)
    allHomeworks = System::getDataInterface()->getHomeworkForGroup(groups[selectedGroupIndex].getID());
    if(users.size()>0)
        commits = System::getDataInterface()->getCommitHomework(users[selectedUserIndex].getID());
}

