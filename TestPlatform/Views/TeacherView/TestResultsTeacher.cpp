#include "ptpch.h"
#include "TestResultsTeacher.h"
#include <raygui.h>

#include "System.h"

TestResultsTeacher::TestResultsTeacher()
{
    groups = System::getDataInterface()->getAllGroups();
    if(groups.size()>0)
    groupUsers = groups[ListView000Active].getUsers();
    if(groupUsers.size()>0)
	userCommits = System::getDataInterface()->getTestResults(groupUsers[ListView002Active].getID());

}

void TestResultsTeacher::update()
{
    if(Button001Pressed)
    {
        System::getInstance()->setMenuView();
    }

}

void TestResultsTeacher::render()
{
    ListView000Active = GuiListView(layoutRecs[0], 
        Helper::ListToStringSeparated(groups,&Group::getName).c_str(), &ListView000ScrollIndex, ListView000Active);

    if (ListView000Active >= 0 && ListView000Active < groups.size() && groups.size()>0) groupSelected = true;
    else groupSelected = false;


    auto lambda = [](User& user)
    {
        return user.getName() + " " + user.getSurname();
    };
    Button001Pressed = GuiButton(layoutRecs[1], "Menu");
    if (groupSelected)
    {
        groupUsers = groups[ListView000Active].getUsers();
        ListView002Active = GuiListView(layoutRecs[2], Helper::ListToStringSeparated(groupUsers, lambda).c_str(), &ListView002ScrollIndex, ListView002Active);

    }

    if (ListView002Active >= 0 && ListView002Active < groupUsers.size() && groupUsers.size()>0) userSelected = true;
    else userSelected = false;
    auto lambda1 = [](TestCommit& commit)
    {
        return std::string(commit.getTest().getTestName() + " " + std::to_string(commit.calculatePercentage())) + "%";
    };
    if (groupSelected && userSelected)
    {
        
        userCommits = System::getDataInterface()->getTestResults(groupUsers[ListView002Active].getID());
        INFO("user commits size {}", groupUsers[ListView002Active].getSurname())
        ListView003Active = GuiListView(layoutRecs[3], Helper::ListToStringSeparated(userCommits, lambda1).c_str(), &ListView003ScrollIndex, ListView003Active);
    }
}
