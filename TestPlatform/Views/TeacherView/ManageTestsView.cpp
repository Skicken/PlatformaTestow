#include "ptpch.h"
#include "ManageTestsView.h"
#include <raygui.h>
#include "System.h"


void ManageTestsView::update()
{
    if (menuButton)
        System::getInstance()->setMenuView();
    if (updateTestButton)
        updateTest();
    if (questionSelected && (addAnswerButton || (answerNameInputEdit && IsKeyPressed(KEY_ENTER))))
        answerAdd();
    if (answerSelected && setCorrectAnswerButton)
        setCorrectAnswer();
    if (answerSelected && removeAnswerButton)
        answerRemove();
    if (testSelected && (addQuestionButton || (questionNameInputEdit && IsKeyPressed(KEY_ENTER) )))
        questionAdd();
    if (questionSelected && removeQuestionButton)
        questionRemove();
    if (addTestButton || (testNameInputEdit && IsKeyPressed(KEY_ENTER)))
        testAdd();
    if (removeTestButton && testSelected)
        testRemove();
    if (assignTestButton && testSelected && groupSelected && !teacherTests[selectedTestIndex].getTestID().empty())
        testAssign();
    if (deassignTestButton && assignedSelected)
        testDeassign();
    tabInput();
}

void ManageTestsView::render()
{

    menuButton = GuiButton(layoutRecs[0], "Menu");

    int previous = selectedGroupIndex;
    selectedGroupIndex = GuiListView(layoutRecs[1], Helper::ListToStringSeparated(groups,&Group::getName).c_str(), &ListView001ScrollIndex, selectedGroupIndex);
    groupSelected = selectedGroupIndex >= 0 && selectedGroupIndex < groups.size();

    if (groupSelected)
    {   if(previous!= selectedGroupIndex)
        assignedTests = System::getDataInterface()->getAllAssignedTests(groups[selectedGroupIndex], *System::getLoggedUser());

        selectedAssignedTestIndex = GuiListView(layoutRecs[2], Helper::ListToStringSeparated(assignedTests, &Test::getTestName).c_str(), &ListView002ScrollIndex, selectedAssignedTestIndex);
        deassignTestButton = GuiButton(layoutRecs[9], "Remove Test Assignment");

    }
    assignedSelected = selectedAssignedTestIndex >= 0 && selectedAssignedTestIndex < assignedTests.size() && groupSelected;
    

    selectedTestIndex = GuiListView(layoutRecs[3], Helper::ListToStringSeparated(teacherTests, &Test::getTestName).c_str(), &ListView003ScrollIndex, selectedTestIndex);
    testSelected = selectedTestIndex >= 0 && selectedTestIndex < teacherTests.size();


    if (testSelected)
    {
        testQuestions = teacherTests[selectedTestIndex].getQuestions();
        selectedQuestionIndex = GuiListView(layoutRecs[4], Helper::ListToStringSeparated(testQuestions, &Question::getQuestionName).c_str(), &ListView004ScrollIndex, selectedQuestionIndex);
    }
    questionSelected = selectedQuestionIndex >= 0 && selectedQuestionIndex < testQuestions.size() && testSelected;
    if (questionSelected)
    {
        questionAnswers = testQuestions[selectedQuestionIndex].getAnswers();
        selectedAnswerIndex = GuiListView(layoutRecs[5], Helper::ListToStringSeparated(questionAnswers, &Answer::getAnswer).c_str(), &ListView005ScrollIndex, selectedAnswerIndex);
    }
    answerSelected = selectedAnswerIndex >= 0 && selectedAnswerIndex < questionAnswers.size() && questionSelected;


    if(questionSelected)
    GuiDummyRec(layoutRecs[6], testQuestions[selectedQuestionIndex].getCorrectAnswer().getAnswer().c_str());

    //TEST
    if (GuiTextBox(layoutRecs[7], testNameInput, 128, testNameInputEdit)) testNameInputEdit = !testNameInputEdit;


    addTestButton = GuiButton(layoutRecs[10], "Add Test");
    assignTestButton = GuiButton(layoutRecs[11], "Assign Test");
    removeTestButton = GuiButton(layoutRecs[12], "Remove Test");
    if (testSelected)
    {
        if (GuiTextBox(layoutRecs[8], questionNameInput, 128, questionNameInputEdit)) questionNameInputEdit = !questionNameInputEdit;
        addQuestionButton = GuiButton(layoutRecs[13], "Add Question");
        removeQuestionButton = GuiButton(layoutRecs[14], "Remove Question");
    }
    if (questionSelected)
    {
        if (GuiTextBox(layoutRecs[18], answerNameInput, 128, answerNameInputEdit)) answerNameInputEdit = !answerNameInputEdit;
        addAnswerButton = GuiButton(layoutRecs[15], "Add Answer");
        setCorrectAnswerButton = GuiButton(layoutRecs[16], "Set Correct");
        removeAnswerButton = GuiButton(layoutRecs[17], "Remove Answer");
    }
    updateTestButton = GuiButton(layoutRecs[19], "Update Test");


}

ManageTestsView::ManageTestsView()
{
    testNameInputEdit = true;
    refreshData();
}

void ManageTestsView::questionRemove()
{
    testQuestions.erase(testQuestions.begin() + selectedQuestionIndex);
    teacherTests[selectedTestIndex].setQuestions(testQuestions);
}

void ManageTestsView::updateTest()
{
    if(testSelected)
    {
        teacherTests[selectedTestIndex].setQuestions(testQuestions);
        Test& test = teacherTests[selectedTestIndex];
        try
        {
            System::getDataInterface()->modifyTest(test,
                System::getLoggedUser()->getID());
            DrawText("Invalid test Data", 600, 960, 15, RED);

        }catch(ExternalData::DatabaseException &exception)
        {
            INFO("{}", exception.what())
        }
        catch(sql::SQLException &exception)
        {
            ERROR(exception.what())
        }
        refreshData();
    }
}

void ManageTestsView::refreshData()
{
    selectedGroupIndex = 0;
    selectedAssignedTestIndex = 0;
    selectedTestIndex = 0;
    selectedQuestionIndex = 0;
    selectedAnswerIndex = 0;

    groups = System::getDataInterface()->getAllGroups();
    if (!groups.empty())
        assignedTests = System::getDataInterface()->getAllAssignedTests(groups[selectedGroupIndex], *System::getLoggedUser());
    teacherTests = System::getDataInterface()->getTeacherTests(System::getLoggedUser()->getID());
    if (!teacherTests.empty())
    {
        testQuestions = teacherTests[selectedQuestionIndex].getQuestions();
        if (!testQuestions.empty())
        {
            questionAnswers = testQuestions[selectedAnswerIndex].getAnswers();
        }
    }
}

void ManageTestsView::testAdd()
{
    if (std::string(testNameInput).size() < 5) return;
    Test test(testNameInput);
    teacherTests.push_back(test);
    memset(testNameInput, 0, sizeof testNameInput);
    selectedTestIndex = teacherTests.size() - 1;


}

void ManageTestsView::testRemove()
{
    System::getDataInterface()->deleteTest(teacherTests[selectedTestIndex]);
    refreshData();
}

void ManageTestsView::questionAdd()
{
    if (std::string(questionNameInput).size() < 5) return;
    Question question(questionNameInput);
    testQuestions.push_back(question);
    teacherTests[selectedTestIndex].setQuestions(testQuestions);
    selectedQuestionIndex = testQuestions.size() - 1;
    memset(questionNameInput, 0, sizeof questionNameInput);

}

void ManageTestsView::answerAdd()
{
    if (std::string(answerNameInput).empty()) return;
    questionAnswers.push_back(answerNameInput);
    if (questionAnswers.size() <= 1) {
        Answer correctAnswer = questionAnswers[0];
        testQuestions[selectedQuestionIndex].setCorrectAnswer(correctAnswer);
    }
    testQuestions[selectedQuestionIndex].setAnswers(questionAnswers);
    teacherTests[selectedTestIndex].setQuestions(testQuestions);
    selectedAnswerIndex = questionAnswers.size() - 1;

    memset(answerNameInput, 0, sizeof answerNameInput);

}

void ManageTestsView::answerRemove()
{
    questionAnswers.erase(questionAnswers.begin() + selectedAnswerIndex);
    testQuestions[selectedQuestionIndex].setAnswers(questionAnswers);
    teacherTests[selectedTestIndex].setQuestions(testQuestions);
}

void ManageTestsView::setCorrectAnswer()
{
    Answer correctAnswer = questionAnswers[selectedAnswerIndex];
    testQuestions[selectedQuestionIndex].setCorrectAnswer(correctAnswer);
    teacherTests[selectedTestIndex].setQuestions(testQuestions);
}

void ManageTestsView::testDeassign()
{
    System::getDataInterface()->deassignTest(groups[selectedGroupIndex], assignedTests[selectedAssignedTestIndex]);
    assignedTests = System::getDataInterface()->getAllAssignedTests(groups[selectedGroupIndex], *System::getLoggedUser());
}

void ManageTestsView::tabInput()
{
    if(IsKeyPressed(KEY_TAB))
    {
        *tabIndex[currentTabIndex] = false;
        ++currentTabIndex%=3;
        *tabIndex[currentTabIndex] = true;
    }
}

void ManageTestsView::testAssign()
{
    System::getDataInterface()->assignTest(groups[selectedGroupIndex], teacherTests[selectedTestIndex]);
    assignedTests = System::getDataInterface()->getAllAssignedTests(groups[selectedGroupIndex], *System::getLoggedUser());
}
