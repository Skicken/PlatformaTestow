#pragma once
#include "View.h"
class Mail :
    public View
{
public:
	Mail();

	void update() override;
		void render() override;
	private:
		EmailWrapper::MailSender sender;
        std::vector<User> users;
        std::vector<Group> groups;
		void sendMail();
		void renderUserRecipents();
		void renderGroupsRecipents();
	std::string errorMessage = "";
	bool toggleSwitch = false;
    int ListView000ScrollIndex = 0;
    int ListView000Active = 0;
    bool Toggle001Active = false;
    bool Button002Pressed = false;
    bool TextmultiBox003EditMode = false;
    char TextmultiBox003Text[128] = "";
    bool Button004Pressed = false;
    bool TextBox006EditMode = false;
    char TextBox006Text[128] = "";
    bool TextBox008EditMode = false;
    char TextBox008Text[128] = "";

    Rectangle layoutRecs[10] = {
        { 144, 192, 408, 720 },
        { 248, 144, 208, 24 },
        { 880, 768, 208, 48 },
        { 744, 360, 472, 328 },
        { 48, 24, 216, 48 },
        { 744, 336, 120, 24 },
        { 744, 296, 480, 24 },
        { 744, 280, 120, 24 },
        { 744, 240, 480, 24 },
        { 744, 216, 120, 24 },
    };
    //----
};

