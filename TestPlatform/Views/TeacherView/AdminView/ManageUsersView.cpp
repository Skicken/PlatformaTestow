#include "ptpch.h"
#include "ManageUsersView.h"
#include <raygui.h>
#include "System.h"
#include "Utilities/ClassToStringFormatter.h"

ManageUsersView::ManageUsersView()
{
    refreshData();
}

void ManageUsersView::setInputFromSelected()
{
    if (!userSelected){
        resetInput();
        return;
    }
    User& user = users[selectedUserIndex];
    strcpy(nameInput,user.getName().c_str());
    strcpy(surnameInput, user.getSurname().c_str());
    strcpy(emailInput, user.getEmail().c_str());
    accountTypeSelected = static_cast<int>(user.getType());

}

void ManageUsersView::resetInput()
{
    memset(nameInput, 0, sizeof nameInput);
    memset(surnameInput, 0, sizeof surnameInput);
    memset(emailInput, 0, sizeof emailInput);
    memset(loginInput, 0, sizeof loginInput);
    memset(passwordInput, 0, sizeof passwordInput);
    accountTypeSelected = 0;

}

void ManageUsersView::update()
{
    if (menuButton) System::getInstance()->setMenuView();
    if (addUserButton) addUser();
    if (removeUserButton) removeUser();
    if (updateUserButton) updateUser();
    if (addUserGroupButton) addUserToGroup();
    if (removeUserGroupButton) removeUserFromGroup();
    if (addGroupButton) addGroup();
    if (removeGroupButton) removeGroup();
    tabInput();
}

void ManageUsersView::render()
{
    if (accountTypeEdit) GuiLock();

    menuButton = GuiButton(layoutRecs[0], "MENU");
    int previous = selectedUserIndex;
    selectedUserIndex = GuiListView(layoutRecs[1], 
    Helper::ListToStringSeparated(users,ClassToStringFormatter::userToStringWithType).c_str(), &ListView001ScrollIndex, selectedUserIndex);
    userSelected = selectedUserIndex >= 0 && selectedUserIndex < users.size();
    if (previous != selectedUserIndex && userSelected) setInputFromSelected();

    if (GuiTextBox(layoutRecs[2], nameInput, 128, nameEdit)) nameEdit = !nameEdit;
    if (GuiTextBox(layoutRecs[3], surnameInput, 128, surnameEdit)) surnameEdit = !surnameEdit;
    if (GuiTextBox(layoutRecs[4], emailInput, 128, emailEdit)) emailEdit = !emailEdit;
    if (GuiTextBox(layoutRecs[5], loginInput, 128, loginEdit)) loginEdit = !loginEdit;
    if (GuiTextBox(layoutRecs[6], passwordInput, 128, passwordEdit)) passwordEdit = !passwordEdit;
    addUserButton = GuiButton(layoutRecs[8], "ADD USER");
    removeUserButton = GuiButton(layoutRecs[9], "REMOVE USER");
    updateUserButton = GuiButton(layoutRecs[10], "UPDATE USER");


    selectedGroupIndex = GuiListView(layoutRecs[11], Helper::ListToStringSeparated(groups, ClassToStringFormatter::groupToString).c_str(), &ListView011ScrollIndex, selectedGroupIndex);
    groupSelected = selectedGroupIndex >= 0 && selectedGroupIndex < groups.size();

    addUserGroupButton = GuiButton(layoutRecs[12], "Add User to Group");
    addGroupButton = GuiButton(layoutRecs[14], "Add Group");
    removeGroupButton = GuiButton(layoutRecs[15], "Remove Group");
    if (GuiTextBox(layoutRecs[16], groupNameInput, 128, groupEdit)) groupEdit = !groupEdit;

    GuiLabel(layoutRecs[17], "Name");
    GuiLabel(layoutRecs[18], "Surname");
    GuiLabel(layoutRecs[19], "Email");
    GuiLabel(layoutRecs[20], "Login");
    GuiLabel(layoutRecs[21], "Password");
    GuiLabel(layoutRecs[23], "Account Type");
    groupUserSelected = false;
    if (groupSelected)
    {
        removeUserGroupButton = GuiButton(layoutRecs[13], "Remove user from Group");
        std::vector<User> groupUsers = groups[selectedGroupIndex].getUsers();
        selectedGroupUserIndex = GuiListView(layoutRecs[24], Helper::ListToStringSeparated(groupUsers, ClassToStringFormatter::userToString).c_str(), &ListView025ScrollIndex, selectedGroupUserIndex);
        groupUserSelected = selectedGroupUserIndex >= 0 && selectedGroupUserIndex < groupUsers.size();

    }
    
    if (GuiDropdownBox(layoutRecs[7], "student;teacher;admin", &accountTypeSelected, accountTypeEdit)) accountTypeEdit = !accountTypeEdit;
    if(!error.empty())
    {
        DrawText(error.c_str(), 48, 720, 10, RED);
    }
    GuiUnlock();
}

void ManageUsersView::refreshData()
{
    groups = System::getDataInterface()->getAllGroups();
    users = System::getDataInterface()->getAllUsers();
}

void ManageUsersView::tabInput()
{
    if (IsKeyPressed(KEY_TAB))
    {
        *tabIndex[currentTabIndex] = false;
        ++currentTabIndex %= 5;
        *tabIndex[currentTabIndex] = true;
    }
}
void ManageUsersView::addUser()
{
    User user(nameInput, surnameInput, emailInput, static_cast<UserType>(accountTypeSelected));
    try
    {
        System::getDataInterface()->addUser(user, loginInput, passwordInput);
    }
    catch (ExternalData::DatabaseException& exception)
    {
        error = exception.what();
    }
    resetInput();
    refreshData();
}

void ManageUsersView::removeUser()
{
    if (!userSelected) return;
    if (users[selectedUserIndex].getID() != System::getLoggedUser()->getID())
    {
        System::getDataInterface()->deleteUser(users[selectedUserIndex]);
    }
    else
    {
        error = "Cannot delete user currently logged";
    }
    refreshData();
}

void ManageUsersView::updateUser()
{
    if (!userSelected) return;

    User user(users[selectedUserIndex]);
    user.setName(nameInput);
    user.setSurname(surnameInput);
    user.setEmail(emailInput);
    user.setType(static_cast<UserType>(accountTypeSelected));
    try {
        System::getDataInterface()->modifyUser(user, loginInput, passwordInput);
    }
    catch (ExternalData::DatabaseException& exception)
    {
        error = exception.what();
    }
    resetInput();
    refreshData();
}

void ManageUsersView::addUserToGroup()
{
    
    if (!userSelected || !groupSelected)  return;

    try {
        System::getDataInterface()->addUserToGroup(users[selectedUserIndex], groups[selectedGroupIndex]);
    }
    catch (sql::SQLException& exception) {}
    refreshData();
}

void ManageUsersView::removeUserFromGroup()
{
    if (!groupUserSelected)  return;
    System::getDataInterface()->removeUserFromGroup(users[selectedGroupUserIndex], groups[selectedGroupIndex]);
    refreshData();

}

void ManageUsersView::addGroup()
{
    Group group(groupNameInput);
	System::getDataInterface()->addGroup(group);
    refreshData();
}

void ManageUsersView::removeGroup()
{
    if (!groupSelected) return;
    Group group(groupNameInput);
    System::getDataInterface()->deleteGroup(groups[selectedGroupIndex]);
    refreshData();

}
