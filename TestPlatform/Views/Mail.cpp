#include "ptpch.h"
#include "Mail.h"
#include <raygui.h>
#include "System.h"

Mail::Mail()
{
    users = System::getDataInterface()->getAllUsers();
    groups = System::getDataInterface()->getAllGroups();
}

void Mail::update()
{
    if(Button004Pressed)
    {
        System::getInstance()->setMenuView();
    }
    if(toggleSwitch) ListView000Active = 0;
    if (Button002Pressed) sendMail();

}

void Mail::render()
{


    bool temp = Toggle001Active;

    Toggle001Active = GuiToggle(layoutRecs[1], "Group Recipent", Toggle001Active);
    toggleSwitch = Toggle001Active ^ temp;
    Button002Pressed = GuiButton(layoutRecs[2], "Send Mail");
    if (GuiTextBoxMulti(layoutRecs[3], TextmultiBox003Text, 128, TextmultiBox003EditMode)) TextmultiBox003EditMode = !TextmultiBox003EditMode;
    Button004Pressed = GuiButton(layoutRecs[4], "Menu");
    GuiLabel(layoutRecs[5], "Message");
    if (GuiTextBox(layoutRecs[6], TextBox006Text, 128, TextBox006EditMode)) TextBox006EditMode = !TextBox006EditMode;
    GuiLabel(layoutRecs[7], "Title");
    if (GuiTextBox(layoutRecs[8], TextBox008Text, 128, TextBox008EditMode)) TextBox008EditMode = !TextBox008EditMode;
    GuiLabel(layoutRecs[9], "Password to your email");

	if(!errorMessage.empty()) 
    DrawText(errorMessage.c_str(), 744, 712, 15, RED);
    if(Toggle001Active)
    {
        renderGroupsRecipents();
    }
    else
    {
        renderUserRecipents();
    }
    DrawText(System::getInstance()->getLoggedUser()->getEmail().c_str(), 875, 223, 10, GREEN);

}

void Mail::sendMail()
{
    
    if(Toggle001Active && ListView000Active>=0 && ListView000Active<groups.size())
    {
        User& user = *System::getInstance()->getLoggedUser();
        Sender s(user, user.getEmail(), TextBox008Text);
        try {
            sender.sendToGroup(s, SimplifiedMessage(TextBox006Text, TextmultiBox003Text), groups[ListView000Active]);
        }catch(mailio::smtp_error&error)
        {
            errorMessage = error.what();
        }
        catch(mailio::dialog_error&error)
        {
            errorMessage = error.what();
        }
    }
    else if(ListView000Active >= 0 && ListView000Active < users.size())
    {
        User& user = *System::getInstance()->getLoggedUser();
        Sender s(user, user.getEmail(), TextBox008Text);
        try{
        sender.sendToUser(s, SimplifiedMessage(TextBox006Text, TextmultiBox003Text), users[ListView000Active]);
	    }
	    catch (mailio::smtp_error& error)
	    {
	        errorMessage = error.what();
	    }
    }
}
void Mail::renderUserRecipents()
{
    auto lambda = [](User& user)
    {
        return user.getName()+" "+user.getSurname();
    };
    ListView000Active = GuiListView(layoutRecs[0], Helper::ListToStringSeparated(users, lambda).c_str(), &ListView000ScrollIndex, ListView000Active);
}

void Mail::renderGroupsRecipents()
{
    auto lambda = [](Group& group)
    {
        return group.getName();
    };
    ListView000Active = GuiListView(layoutRecs[0], Helper::ListToStringSeparated(groups, lambda).c_str(), &ListView000ScrollIndex, ListView000Active);
}
