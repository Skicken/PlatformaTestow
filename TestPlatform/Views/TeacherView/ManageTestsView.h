#pragma once
#include "Views/View.h"

class ManageTestsView : public View
{
	public:
	void update() override;
	void render() override;
    ManageTestsView();
	private:
        void questionRemove();
        void testAssign();
        void updateTest();
        void refreshData();
        void testAdd();
        void testRemove();
        void questionAdd();
        void answerAdd();
        void answerRemove();
        void setCorrectAnswer();
        void testDeassign();
        void tabInput();
	std::vector<Group> groups;
    std::vector<Test> assignedTests;

    std::vector<Test> teacherTests;
    std::vector<Question> testQuestions;
    std::vector<Answer> questionAnswers;

    bool groupSelected = false;
    bool testSelected = false;
    bool questionSelected = false;
    bool answerSelected = false;
    bool assignedSelected = false;
	bool menuButton = false;
    int selectedGroupIndex = 0;
    int selectedAssignedTestIndex = 0;
    int selectedTestIndex = 0;
    int selectedQuestionIndex = 0;
    int selectedAnswerIndex = 0;
    bool testNameInputEdit = false;
    char testNameInput[128] = "";
    bool questionNameInputEdit = false;
    char questionNameInput[128] = "";

     bool* const tabIndex[3] = { &testNameInputEdit,&questionNameInputEdit,&answerNameInputEdit };
    int currentTabIndex = 0;

    bool deassignTestButton = false;
    bool addTestButton = false;
    bool assignTestButton = false;
    bool removeTestButton = false;
    bool addQuestionButton = false;
    bool removeQuestionButton = false;
    bool addAnswerButton = false;
    bool setCorrectAnswerButton = false;
    bool removeAnswerButton = false;
    bool answerNameInputEdit = false;
    char answerNameInput[128] = "";
    bool updateTestButton = false;

    int ListView001ScrollIndex = 0;
    int ListView002ScrollIndex = 0;
    int ListView003ScrollIndex = 0;
    int ListView004ScrollIndex = 0;
    int ListView005ScrollIndex = 0;

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
		{ 600, 888, 360, 56 },

    };
};

