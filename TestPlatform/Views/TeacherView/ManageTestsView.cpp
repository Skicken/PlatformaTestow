#include "ptpch.h"
#include "ManageTestsView.h"
#include <raygui.h>
#include "System.h"

void ManageTestsView::update()
{
    if (Button000Pressed) System::getInstance()->setMenuView();

    if(Button019Pressed)
    {
        updateTest();
    }
    if(questionSelected && Button015Pressed)
    {
        questionAnswers.push_back(TextBox018Text);
        if (questionAnswers.size() <= 1)
            testQuestions[ListView004Active].setCorrectAnswer(questionAnswers[0]);
        testQuestions[ListView004Active].setAnswers(questionAnswers);
        teacherTests[ListView003Active].setQuestions(testQuestions);

    }
    if (answerSelected && Button016Pressed)
    {
        testQuestions[ListView004Active].setCorrectAnswer(questionAnswers[ListView005Active]);
        teacherTests[ListView003Active].setQuestions(testQuestions);

    }
    if (answerSelected && Button017Pressed)
    {
        questionAnswers.erase(questionAnswers.begin() + ListView005Active);
        testQuestions[ListView004Active].setAnswers(questionAnswers);
        teacherTests[ListView003Active].setQuestions(testQuestions);
    }
    if(testSelected && Button013Pressed)
    {
        Question question(TextBox008Text);
        testQuestions.push_back(question);
        teacherTests[ListView003Active].setQuestions(testQuestions);

    }
    if (questionSelected && Button014Pressed)
    {
        testQuestions.erase(testQuestions.begin() + ListView004Active);
        teacherTests[ListView003Active].setQuestions(testQuestions);


    }


}

void ManageTestsView::render()
{

    Button000Pressed = GuiButton(layoutRecs[0], "Menu");

    int previous = ListView001Active;
    ListView001Active = GuiListView(layoutRecs[1], Helper::ListToStringSeparated(groups,&Group::getName).c_str(), &ListView001ScrollIndex, ListView001Active);
    groupSelected = ListView001Active >= 0 && ListView001Active < groups.size();

    if (groupSelected)
    {   if(previous!= ListView001Active)
        assignedTests = System::getDataInterface()->getAllAssignedTests(groups[ListView001Active], *System::getLoggedUser());

        ListView002Active = GuiListView(layoutRecs[2], Helper::ListToStringSeparated(assignedTests, &Test::getTestName).c_str(), &ListView002ScrollIndex, ListView002Active);
    }

    

    ListView003Active = GuiListView(layoutRecs[3], Helper::ListToStringSeparated(teacherTests, &Test::getTestName).c_str(), &ListView003ScrollIndex, ListView003Active);
    testSelected = ListView003Active >= 0 && ListView003Active < teacherTests.size();


    if (testSelected)
    {
        testQuestions = teacherTests[ListView003Active].getQuestions();
        ListView004Active = GuiListView(layoutRecs[4], Helper::ListToStringSeparated(testQuestions, &Question::getQuestionName).c_str(), &ListView004ScrollIndex, ListView004Active);
    }
    questionSelected = ListView004Active >= 0 && ListView004Active < testQuestions.size() && testSelected;
    if (questionSelected)
    {
        questionAnswers = testQuestions[ListView004Active].getAnswers();
        ListView005Active = GuiListView(layoutRecs[5], Helper::ListToStringSeparated(questionAnswers, &Answer::getAnswer).c_str(), &ListView005ScrollIndex, ListView005Active);
    }
    answerSelected = ListView005Active >= 0 && ListView005Active < questionAnswers.size() && questionSelected;


    if(questionSelected)
    GuiDummyRec(layoutRecs[6], testQuestions[ListView004Active].getCorrectAnswer().getAnswer().c_str());

    //TEST
    if (GuiTextBox(layoutRecs[7], TextBox007Text, 128, TextBox007EditMode)) TextBox007EditMode = !TextBox007EditMode;


    Button008Pressed = GuiButton(layoutRecs[9], "Remove Test Assigment");
    Button009Pressed = GuiButton(layoutRecs[10], "Add Test");
    Button010Pressed = GuiButton(layoutRecs[11], "Assign Test");
    Button012Pressed = GuiButton(layoutRecs[12], "Remove Test");
    if (testSelected)
    {
        //Question
        if (GuiTextBox(layoutRecs[8], TextBox008Text, 128, TextBox008EditMode)) TextBox008EditMode = !TextBox008EditMode;
        Button013Pressed = GuiButton(layoutRecs[13], "Add Question");
        Button014Pressed = GuiButton(layoutRecs[14], "Remove Question");
    }
    if (questionSelected)
    {
        //Answer
        if (GuiTextBox(layoutRecs[18], TextBox018Text, 128, TextBox018EditMode)) TextBox018EditMode = !TextBox018EditMode;
        Button015Pressed = GuiButton(layoutRecs[15], "Add Answer");
        Button016Pressed = GuiButton(layoutRecs[16], "Set Correct");
        Button017Pressed = GuiButton(layoutRecs[17], "Remove Answer");
    }
    Button019Pressed = GuiButton(layoutRecs[19], "Update Test");



}

ManageTestsView::ManageTestsView()
{
    groups = System::getDataInterface()->getAllGroups();
    if (groups.size() > 0)
        assignedTests = System::getDataInterface()->getAllAssignedTests(groups[ListView001Active], *System::getLoggedUser());
    teacherTests = System::getDataInterface()->getTeacherTests(System::getLoggedUser()->getID());
    if(teacherTests.size()>0)
    {
        testQuestions = teacherTests[ListView004Active].getQuestions();
        if(testQuestions.size()>0)
        {
            questionAnswers = testQuestions[ListView005Active].getAnswers();
        }
    }
}
void ManageTestsView::updateTest()
{
    if(testSelected && validateTest())
    {
        teacherTests[ListView003Active].setQuestions(testQuestions);
        System::getDataInterface()->modifyTest(teacherTests[ListView003Active],
            System::getLoggedUser()->getID());
    }
}

bool ManageTestsView::validateTest()
{
    return true;
}
