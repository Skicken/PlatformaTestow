#include "ptpch.h"
#include "TestView.h"
#include "QuestionView.h"
#include <raygui.h>

#include "Utilities/ClassToStringFormatter.h"

TestView::TestView()
{
    refresh();

}
void TestView::update()
{
    if (Button001Pressed) System::getInstance()->setMenuView();
    if (Button004Pressed && !availableTests.empty() && ListView000Active >=0 && ListView000Active < availableTests.size()) {

        INFO("Setting test number {}", ListView000Active);
        std::shared_ptr<TestCommit> commit{new TestCommit(availableTests[ListView000Active]) };
        System::getInstance()->setView(
            new QuestionView(commit)
        );
    }
    else if (Button005Pressed && !commitedTests.empty() && ListView002Active >= 0 && ListView002Active < commitedTests.size()) {

        INFO("Setting Commited test number {}", ListView002Active)
            std::shared_ptr<TestCommit> commit = std::make_shared<TestCommit>(commitedTests[ListView002Active]);
        System::getInstance()->setView(
            new QuestionView(commit,true)
        );
    }
}

void TestView::render()
{
    ListView000Active = GuiListView(layoutRecs[0], availableTestString.c_str(), &ListView000ScrollIndex, ListView000Active);
    ListView002Active = GuiListView(layoutRecs[2], commitedTestString.c_str(), &ListView002ScrollIndex, ListView002Active) ;

    Button001Pressed = GuiButton(layoutRecs[1], "Menu");
    Button004Pressed = GuiButton(layoutRecs[3], "Do Test");
    Button005Pressed = GuiButton(layoutRecs[4], "Check commited Test");
}

void TestView::refresh()
{
    availableTests = System::getDataInterface()->
        getStudentAvailableTest(System::getLoggedUser()->getID());
    commitedTests = System::getDataInterface()->getTestResults(System::getLoggedUser()->getID());

    availableTestString = Helper::ListToStringSeparated<Test>(availableTests, &Test::getTestName);
    commitedTestString = Helper::ListToStringSeparated<TestCommit>(commitedTests, ClassToStringFormatter::testCommitToString);
}
