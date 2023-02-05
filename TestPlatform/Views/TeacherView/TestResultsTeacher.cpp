#include "ptpch.h"
#include "TestResultsTeacher.h"
#include <raygui.h>

#include "System.h"
#include "Utilities/ClassToStringFormatter.h"

TestResultsTeacher::TestResultsTeacher()
{
    groups = System::getDataInterface()->getAllGroups();
    if(groups.size()>0)
    groupUsers = groups[selectedGroupIndex].getUsers();
    if(groupUsers.size()>0)
	userCommits = System::getDataInterface()->getTestResults(groupUsers[selectedUserIndex].getID());

}

void TestResultsTeacher::update()
{
    if(menuButton)
    {
        System::getInstance()->setMenuView();
    }

}
void TestResultsTeacher::render()
{
    menuButton = GuiButton(layoutRecs[1], "Menu");

    selectedGroupIndex = GuiListView(layoutRecs[0], 
        Helper::ListToStringSeparated(groups,&Group::getName).c_str(), &ListView000ScrollIndex, selectedGroupIndex);
    groupSelected = selectedGroupIndex >= 0 && selectedGroupIndex < groups.size() && groups.size()>0;


    if (groupSelected)
    {
        groupUsers = groups[selectedGroupIndex].getUsers();
        selectedUserIndex = GuiListView(layoutRecs[2], Helper::ListToStringSeparated(groupUsers, ClassToStringFormatter::userToString).c_str(), &ListView002ScrollIndex, selectedUserIndex);

    }
    userSelected = selectedUserIndex >= 0 && selectedUserIndex < groupUsers.size() && groupUsers.size()>0;
    if (groupSelected && userSelected)
    {
        
        userCommits = System::getDataInterface()->getTestResults(groupUsers[selectedUserIndex].getID());
        selectedTestCommitIndex = GuiListView(layoutRecs[3], Helper::ListToStringSeparated(userCommits, ClassToStringFormatter::testCommitToString).c_str(), &ListView003ScrollIndex, selectedTestCommitIndex);
    }
}
