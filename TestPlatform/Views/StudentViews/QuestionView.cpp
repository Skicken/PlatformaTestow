#include "ptpch.h"
#include "QuestionView.h"
#include <System.h>
#include <raygui.h>

QuestionView::QuestionView(std::shared_ptr<TestCommit> commit, bool preview): testCommit(commit),currentQuestion(testCommit->getCurrentQuestion()),
	preview(preview)
{
	progressBarValue = commit->getProgress();
	selectedAnswer = false;
	INFO(progressBarValue)
}

QuestionView::QuestionView(std::shared_ptr<TestCommit> commit): testCommit(commit), currentQuestion(testCommit->getCurrentQuestion())
{
	currentQuestion = testCommit->getCurrentQuestion();
	progressBarValue = commit->getProgress();
	preview = false;
	selectedAnswer = false;
	INFO(progressBarValue)

}


void QuestionView::update()
{
	if((nextQuestionButton || previousQuestionButton) && selectedAnswer && !preview)
	{
		testCommit->setAnswerForQuestion(testCommit->getCurrentQuestion().getAnswers()[selectedAnswerIndex]);
	}
	if (nextQuestionButton && selectedAnswer)
	{
		goToNextQuestion();
	}
	else if(previousQuestionButton && selectedAnswer)
	{
		goToPreviousQuestion();
	}
	
}

void QuestionView::render()
{
    DrawText(testCommit->getCurrentQuestion().getQuestionName().c_str(), 288, 216, 40, GRAY);

	if (preview) {
		selectedAnswerIndex = testCommit->getCurrentQuestionAnswerIndex();
		GuiListView(layoutRecs[4],
			Helper::ListToStringSeparated(testCommit->getCurrentQuestion().getAnswers(), &Answer::getAnswer).c_str(),
			&ListView005ScrollIndex, selectedAnswerIndex);
		DrawText("Test Preview", 288, 150, 20, GREEN);
	}
	else
	{
		selectedAnswerIndex = GuiListView(layoutRecs[4],
			Helper::ListToStringSeparated(testCommit->getCurrentQuestion().getAnswers(), &Answer::getAnswer).c_str(),
			&ListView005ScrollIndex, selectedAnswerIndex);
	}
	selectedAnswer = selectedAnswerIndex >= 0 && selectedAnswerIndex < testCommit->getCurrentQuestion().getAnswers().size();
    progressBarValue = GuiProgressBar(layoutRecs[0], NULL, NULL, progressBarValue, 0, 1);

	if(testCommit->isLastQuestion())
		nextQuestionButton = GuiButton(layoutRecs[1], "Finish Test");
	else
		nextQuestionButton = GuiButton(layoutRecs[1], "Next Question");
	std::string percent = std::to_string(testCommit->getProgress() * 100);
	percent = percent.substr(0, 5);
	const std::string progressLabel = "Progress Bar " + percent +" %";
    GuiLabel(layoutRecs[2], progressLabel.c_str());
    previousQuestionButton = GuiButton(layoutRecs[3], "Previous Question");
}
void QuestionView::goToPreviousQuestion()
{

	if (testCommit->getPreviousQuestion())
	{
		System::getInstance()->setView(new QuestionView(testCommit, preview));
		return;
	}

}

void QuestionView::goToNextQuestion()
{
	if (testCommit->getNextQuestion())
	{
		System::getInstance()->setView(new QuestionView(testCommit, preview));
		return;
	}
	if (!preview) {
		System::getDataInterface()->commitTestResult(*testCommit,
			System::getInstance()->getLoggedUser()->getID());
	}
	System::getInstance()->setMenuView();
	
}
