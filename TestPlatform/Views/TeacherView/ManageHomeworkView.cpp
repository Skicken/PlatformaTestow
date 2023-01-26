#include "ptpch.h"
#include "ManageHomeworkView.h"
#include <raygui.h>

#include "System.h"
ManageHomeworkView::ManageHomeworkView()
{
    refreshData();
}
void ManageHomeworkView::update()
{
    if (Button001Pressed) System::getInstance()->setMenuView();
    if(LabelButton004Pressed && homeworkSelected)
    {
        System::getDataInterface()->deleteHomework(allHomeworks[ListView002Active]);

        refreshData();
    }
    if(Button003Pressed && groupSelected)
    {
        Homework home(TextBox000Text);
    	System::getDataInterface()->addHomework(groups[ListView008Active],home);
        refreshData();
    }
}

void ManageHomeworkView::render()
{
    if (GuiTextBox(layoutRecs[0], TextBox000Text, 128, TextBox000EditMode)) TextBox000EditMode = !TextBox000EditMode;

    int previous = ListView008Active;
    ListView008Active = GuiListView(layoutRecs[8], Helper::ListToStringSeparated(groups,&Group::getName).c_str(), &ListView008ScrollIndex, ListView008Active);
    groupSelected = ListView008Active >= 0 && ListView008Active < groups.size();
    if (groupSelected) {
        if (previous != ListView008Active) allHomeworks = System::getDataInterface()->getHomeworkForGroup(groups[ListView008Active].getID());
        INFO(allHomeworks.size());
        ListView002Active = GuiListView(layoutRecs[2], Helper::ListToStringSeparated(allHomeworks, &Homework::getQuestion).c_str(), &ListView002ScrollIndex, ListView002Active);
        homeworkSelected = ListView002Active >= 0 && ListView002Active < allHomeworks.size();
    }

    auto lambda1 = [](User& user)
    {
        return user.getName() + " " + user.getSurname();
    };
     previous = ListView005Active;
    ListView005Active = GuiListView(layoutRecs[5], Helper::ListToStringSeparated(users, lambda1 ).c_str(), &ListView005ScrollIndex, ListView005Active);
    userSelected = ListView005Active >= 0 && ListView005Active < users.size();
    auto lambda2 = [](HomeworkCommit& commit)
    {
        return commit.getDeliveryDate() + " : " + commit.getQuestion();
    };
    if (userSelected)
    {
        if (previous != ListView005Active) commits = System::getDataInterface()->getCommitHomework(users[ListView005Active].getID());
        ListView006Active = GuiListView(layoutRecs[6], Helper::ListToStringSeparated(commits, lambda2).c_str(), &ListView006ScrollIndex, ListView006Active);

    }
    homeworkCommitSelected = ListView006Active >= 0 && ListView006Active < commits.size() && userSelected;

    if (homeworkCommitSelected)
    {
        std::string answerHomework = commits[ListView006Active].getAnswer();
        GuiTextBoxMulti(layoutRecs[7], const_cast<char*>(answerHomework.c_str()), 128, TextmultiBox007EditMode);
    }

    Button001Pressed = GuiButton(layoutRecs[1], "Menu");
    Button003Pressed = GuiButton(layoutRecs[3], "Add Homework");
    LabelButton004Pressed = GuiButton(layoutRecs[4], "Delete Homework");
}



void ManageHomeworkView::refreshData()
{
    groups = System::getDataInterface()->getAllGroups();
    users = System::getDataInterface()->getAllUsers();
    if(groups.size()>0)
    allHomeworks = System::getDataInterface()->getHomeworkForGroup(groups[ListView008Active].getID());
    if(users.size()>0)
        commits = System::getDataInterface()->getCommitHomework(users[ListView005Active].getID());
}
