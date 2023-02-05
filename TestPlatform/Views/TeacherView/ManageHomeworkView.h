#pragma once
#include "Views/View.h"

class ManageHomeworkView : public View
{
	public:
		void update() override;
		void render() override;
        ManageHomeworkView();
	private:

	void refreshData();
	std::vector<Group> groups;
	std::vector<Homework> allHomeworks;
    std::vector<User> users;
    std::vector<HomeworkCommit> commits;

    bool groupSelected = false;
    bool homeworkCommitSelected = false;
    bool userSelected = false;
    bool homeworkSelected = false;

	bool homeworkNameEdit = false;
    char homeworkNameInput[128] = "";
    bool menuButton = false;
    int selectedHomeworkIndex = 0;
    bool addHomeworkButton = false;
    bool deleteHomeworkButton = false;
    int ListView005ScrollIndex = 0;
    int selectedUserIndex = 0;
    int selectedHomeworkCommitIndex = 0;
    bool viewHomeworkEdit = false;
	int selectedGroupIndex = 0;

    int ListView002ScrollIndex = 0;
    int ListView006ScrollIndex = 0;
    int ListView008ScrollIndex = 0;

    Rectangle layoutRecs[9] = {
        { 360, 120, 384, 48 },
        { 24, 48, 216, 48 },
        { 360, 192, 384, 624 },
        { 360, 840, 128, 48 },
        { 616, 840, 128, 48 },
        { 784, 192, 312, 624 },
        { 1176, 192, 312, 624 },
        { 1560, 192, 336, 624 },
        { 8, 192, 312, 624 },
    };

};

