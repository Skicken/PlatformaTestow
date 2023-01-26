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

	bool TextBox000EditMode = false;
    char TextBox000Text[128] = "";
    bool Button001Pressed = false;
    int ListView002ScrollIndex = 0;
    int ListView002Active = 0;
    bool Button003Pressed = false;
    bool LabelButton004Pressed = false;
    int ListView005ScrollIndex = 0;
    int ListView005Active = 0;
    int ListView006ScrollIndex = 0;
    int ListView006Active = 0;
    bool TextmultiBox007EditMode = false;
    char TextmultiBox007Text[128] = "SAMPLE TEXT";

	int ListView008Active = 0;
    int ListView008ScrollIndex = 0;

    Rectangle layoutRecs[9] = {
        { 360, 120, 384, 48 },
        { 48, 24, 264, 48 },
        { 360, 192, 384, 624 },
        { 360, 840, 128, 48 },
        { 616, 840, 128, 48 },
        { 784, 192, 312, 624 },
        { 1176, 192, 312, 624 },
        { 1560, 192, 336, 624 },
        { 8, 192, 312, 624 },
    };

};

