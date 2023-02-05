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
		EmailWrapper::MailSender mailSender;
        std::vector<User> users;
        std::vector<Group> groups;
		void sendMail();
		void renderUserRecipents();
		void renderGroupsRecipents();
        void showPasswordInput();


	std::string errorMessage = "";
	bool toggleSwitch = false;
    int selectedRecipentIndex = 0;
    bool groupRecipentToggle = false;
    bool sendMailButton = false;
    bool mailMessageEdit = false;
    char mailMessageInput[128] = "";
    bool menuButton = false;
    bool mailTitleEdit = false;
    char mailTitleInput[128] = "";
    bool passwordEdit = false;
    char passwordInput[128] = "";

    Rectangle layoutRecs[10] = {
        { 144, 192, 408, 720 },
        { 248, 144, 208, 24 },
        { 880, 768, 208, 48 },
        { 744, 360, 472, 328 },
        { 24, 48, 216, 48 },
        { 744, 336, 120, 24 },
        { 744, 296, 480, 24 },
        { 744, 280, 120, 24 },
        { 744, 240, 480, 24 },
        { 744, 216, 120, 24 },
    };
    int ListView000ScrollIndex = 0;

    //----
};

