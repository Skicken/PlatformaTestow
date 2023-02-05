#pragma once
#include "Views/View.h"

class HomeworkView : public View
{
public:
	HomeworkView();

	void update() override;
	void render() override;
	private:
	void refreshData();
	std::vector<Homework> homeworks;

	int ListView000ScrollIndex = 0;
    int ListView000Active = 0;
    bool Button002Pressed = false;
    bool homeworkEditMode = false;
    char homeworkText[256] = "write Homework";
    bool Button003Pressed = false;
    

    Rectangle layoutRecs[4] = {
        { 336, 120, 320, 744 },
        { 24, 48, 216, 48 },
        { 800, 120, 352, 744 },
        { 872, 888, 216, 48 },
    };
};

