#include "ptpch.h"
#include "Mail.h"
#include <raygui.h>
#include "System.h"
#include "Utilities/ClassToStringFormatter.h"

Mail::Mail()
{
    users = System::getDataInterface()->getAllUsers();
    groups = System::getDataInterface()->getAllGroups();
}

void Mail::update()
{
    if(menuButton)
    {
        System::getInstance()->setMenuView();
    }
    if(toggleSwitch) selectedRecipentIndex = 0;
    if (sendMailButton) sendMail();

}

void Mail::render()
{


    bool previousToggleState = groupRecipentToggle;

    groupRecipentToggle = GuiToggle(layoutRecs[1], "Group Recipent", groupRecipentToggle);
    toggleSwitch = groupRecipentToggle ^ previousToggleState;
    sendMailButton = GuiButton(layoutRecs[2], "Send Mail");
    if (GuiTextBoxMulti(layoutRecs[3], mailMessageInput, 128, mailMessageEdit)) mailMessageEdit = !mailMessageEdit;
    menuButton = GuiButton(layoutRecs[4], "Menu");
    GuiLabel(layoutRecs[5], "Message");
    if (GuiTextBox(layoutRecs[6], mailTitleInput, 128, mailTitleEdit)) mailTitleEdit = !mailTitleEdit;
    GuiLabel(layoutRecs[7], "Title");

	if(!errorMessage.empty()) 
    DrawText(errorMessage.c_str(), 744, 712, 15, RED);
    if(groupRecipentToggle)
    {
        renderGroupsRecipents();
    }
    else
    {
        renderUserRecipents();
    }

}

void Mail::sendMail()
{
    
    if(groupRecipentToggle && selectedRecipentIndex>=0 && selectedRecipentIndex<groups.size())
    {
        User& user = *System::getInstance()->getLoggedUser();
        Sender sender(user, user.getEmail(), passwordInput);
        try {
            mailSender.sendToGroup(sender, SimplifiedMessage(mailTitleInput, mailMessageInput), groups[selectedRecipentIndex]);
        }catch(mailio::smtp_error&error)
        {
            errorMessage = error.what();
        }
        catch(mailio::dialog_error&error)
        {
            errorMessage = error.what();
        }
    }
    else if(selectedRecipentIndex >= 0 && selectedRecipentIndex < users.size())
    {
        User& user = *System::getInstance()->getLoggedUser();
        Sender s(user, user.getEmail(), passwordInput);
        try{
        mailSender.sendToUser(s, SimplifiedMessage(mailTitleInput, mailMessageInput), users[selectedRecipentIndex]);
	    }
	    catch (mailio::smtp_error& error)
	    {
	        errorMessage = error.what();
	    }
    }
}
void Mail::renderUserRecipents()
{
    selectedRecipentIndex = GuiListView(layoutRecs[0], Helper::ListToStringSeparated(users, ClassToStringFormatter::userToString).c_str(), &ListView000ScrollIndex, selectedRecipentIndex);
}

void Mail::renderGroupsRecipents()
{

    selectedRecipentIndex = GuiListView(layoutRecs[0], Helper::ListToStringSeparated(groups, ClassToStringFormatter::groupToString).c_str(), &ListView000ScrollIndex, selectedRecipentIndex);
}

void Mail::showPasswordInput()
{
    DrawText(System::getInstance()->getLoggedUser()->getEmail().c_str(), 875, 223, 10, GREEN);
    if (GuiTextBox(layoutRecs[8], passwordInput, 128, passwordEdit)) passwordEdit = !passwordEdit;
    GuiLabel(layoutRecs[9], "Password to your email");
}
