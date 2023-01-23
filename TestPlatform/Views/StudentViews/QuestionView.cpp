#include "ptpch.h"
#include "QuestionView.h"
#include <System.h>
#include <raygui.h>

QuestionView::QuestionView(std::shared_ptr<TestCommit> commit, bool preview): testCommit(commit),
	preview(preview)
{
	ProgressBar000Value = commit->getProgress();

}

QuestionView::QuestionView(std::shared_ptr<TestCommit> commit): testCommit(commit)
{

	ProgressBar000Value = commit->getProgress();
	preview = false;
}

void QuestionView::update()
{
	if (Button002Pressed && ListView005Active>=0 && ListView005Active< testCommit->getCurrentQuestion().getAnswers().size())
	{
		INFO("Set Answer for question {}", testCommit->getCurrentQuestion().getAnswers()[ListView005Active].getAnswer())
		if(!preview) testCommit->setAnswerForQuestion(
			testCommit->getCurrentQuestion().getAnswers()[ListView005Active]
		);

		if (testCommit->getNextQuestion())
		{

			INFO("Going to next question")
			System::getInstance()->setView(new QuestionView(testCommit,preview));
		}
		else
		{
			INFO("Going to Main Menu")

				//commit test result;
			if(!preview)System::getDataInterface()->commitTestResult(*testCommit,
					System::getInstance()->getLoggedUser()->getID());
			System::getInstance()->setMenuView();
		}
	}
	
}

void QuestionView::render()
{
    DrawText(testCommit->getCurrentQuestion().getQuestionName().c_str(), 288, 216, 40, GRAY);

	if (preview) {
		ListView005Active = testCommit->getCurrentQuestionAnswerIndex();
		GuiListView(layoutRecs[4],
			Helper::ListToStringSeparated(testCommit->getCurrentQuestion().getAnswers(), &Answer::getAnswer).c_str(),
			&ListView005ScrollIndex, ListView005Active);
		DrawText("Test Preview", 288, 150, 20, GREEN);
	}
	else
	{
		ListView005Active = GuiListView(layoutRecs[4],
			Helper::ListToStringSeparated(testCommit->getCurrentQuestion().getAnswers(), &Answer::getAnswer).c_str(),
			&ListView005ScrollIndex, ListView005Active);
	}


    ProgressBar000Value = GuiProgressBar(layoutRecs[0], NULL, NULL, ProgressBar000Value, 0, 1);
    Button002Pressed = GuiButton(layoutRecs[1], "Next Question");
	const std::string progressLabel = "Progress Bar " + std::to_string(testCommit->getProgress());
    GuiLabel(layoutRecs[2], progressLabel.c_str());
    Button004Pressed = GuiButton(layoutRecs[3], "Previous Question");
}
