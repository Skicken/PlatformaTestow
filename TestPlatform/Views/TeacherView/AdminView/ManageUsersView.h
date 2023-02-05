#pragma once
#include "Views/View.h"

class ManageUsersView :
    public View
{
	public:
	ManageUsersView();
    void setInputFromSelected();
    void resetInput();
	void addUser();
	void removeUser();
	void updateUser();
	void addUserToGroup();
	void removeUserFromGroup();
	void addGroup();
	void removeGroup();
	void update() override;
		void render() override;
        
	private:
	void refreshData();
    void tabInput();

    std::vector<Group> groups;
    std::vector<User> users;

	bool menuButton = false;
    int selectedUserIndex = 0;
    bool nameEdit = false;
    char nameInput[128] = "";
    bool surnameEdit = false;
    char surnameInput[128] = "";
    bool emailEdit = false;
    char emailInput[128] = "";
    bool loginEdit = false;
    char loginInput[128] = "";
    bool passwordEdit = false;
    char passwordInput[128] = "";
    bool accountTypeEdit = false;
    int accountTypeSelected = 0;
    bool addUserButton = false;
    bool removeUserButton = false;
    bool updateUserButton = false;
    int selectedGroupIndex = 0;
    bool addUserGroupButton = false;
    bool removeUserGroupButton = false;
    bool addGroupButton = false;
    bool removeGroupButton = false;
    bool groupEdit = false;
    char groupNameInput[128] = "";
    int selectedGroupUserIndex = 0;

    bool userSelected = false;
    bool groupSelected = false;
    bool groupUserSelected = false;

    bool* const tabIndex[5] = { &nameEdit,&surnameEdit,&emailEdit,&loginEdit,&passwordEdit };

    int ListView001ScrollIndex = 0;
    int ListView011ScrollIndex = 0;
    int ListView025ScrollIndex = 0;

    std::string error = "";
    Rectangle layoutRecs[25] = {
        { 40, 48, 200, 48 },
        { 360, 144, 360, 720 },
        { 48, 192, 288, 32 },
        { 48, 264, 288, 32 },
        { 48, 336, 288, 32 },
        { 48, 408, 288, 32 },
        { 48, 480, 288, 32 },
        { 48, 544, 288, 32 },
        { 48, 600, 136, 40 },
        { 200, 600, 136, 40 },
        { 120, 656, 136, 40 },
        { 792, 144, 360, 720 },
        { 472, 888, 136, 40 },
        { 1320, 888, 136, 40 },
        { 792, 888, 136, 40 },
        { 1016, 888, 136, 40 },
        { 824, 96, 288, 32 },
        { 48, 168, 120, 24 },
        { 48, 240, 120, 24 },
        { 48, 312, 120, 24 },
        { 48, 384, 120, 24 },
        { 48, 456, 120, 24 },
        { 0, 0, 0, 0 },
        { 48, 520, 120, 24 },
        { 1200, 144, 360, 720 },
    };
	int currentTabIndex = 0;
};

