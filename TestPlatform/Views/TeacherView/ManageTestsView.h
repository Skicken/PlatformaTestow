#pragma once
#include "Views/View.h"

class ManageTestsView : public View
{
	public:
	void update() override;
	void render() override;
    ManageTestsView();
	private:
        void updateTest();
	std::vector<Group> groups;
    std::vector<Test> assignedTests;

    std::vector<Test> teacherTests;
    std::vector<Question> testQuestions;
    std::vector<Answer> questionAnswers;

    bool groupSelected = false;
    bool testSelected = false;
    bool questionSelected = false;
    bool answerSelected = false;


	bool Button000Pressed = false;
    int ListView001ScrollIndex = 0;
    int ListView001Active = 0;
    int ListView002ScrollIndex = 0;
    int ListView002Active = 0;
    int ListView003ScrollIndex = 0;
    int ListView003Active = 0;
    int ListView004ScrollIndex = 0;
    int ListView004Active = 0;
    int ListView005ScrollIndex = 0;
    int ListView005Active = 0;
    bool TextBox007EditMode = false;
    char TextBox007Text[128] = "SAMPLE TEXT";
    bool TextBox008EditMode = false;
    char TextBox008Text[128] = "SAMPLE TEXT";
    bool Button008Pressed = false;
    bool Button009Pressed = false;
    bool Button010Pressed = false;
    bool Button012Pressed = false;
    bool Button013Pressed = false;
    bool Button014Pressed = false;
    bool Button015Pressed = false;
    bool Button016Pressed = false;
    bool Button017Pressed = false;
    bool TextBox018EditMode = false;
    char TextBox018Text[128] = "SAMPLE TEXT";
    bool Button019Pressed = false;
    bool validateTest();
    Rectangle layoutRecs[20] = {
        { 24, 48, 216, 48 },
        { 24, 120, 216, 672 },
        { 312, 120, 216, 672 },
        { 600, 120, 360, 672 },
        { 1008, 120, 336, 672 },
        { 1440, 120, 336, 672 },
        { 1456, 888, 304, 48 },
        { 600, 56, 360, 40 },
        { 1008, 56, 336, 40 },
        { 336, 808, 176, 56 },
        { 600, 808, 104, 56 },
        { 728, 808, 104, 56 },
        { 856, 808, 104, 56 },
        { 1008, 808, 104, 56 },
        { 1240, 808, 104, 56 },
        { 1416, 808, 104, 56 },
        { 1552, 808, 104, 56 },
        { 1696, 808, 104, 56 },
        { 1440, 56, 336, 40 },
		{ 600, 888, 360, 32 },

    };
};

