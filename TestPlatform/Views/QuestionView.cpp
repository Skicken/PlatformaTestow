#include "ptpch.h"
#include "QuestionView.h"
#include <System.h>

QuestionView::QuestionView(TestCommit& commit):testCommit(commit)
{

    Question& question = commit.getCurrentQuestion();
    questionText.Edit(150, 100, 800, 50, 40, question.getQuestionName());
    int startPosY = 200;
    for (auto answer : question.getAnswers())
    {
        buttonsAnswer.push_back({
                Button(150,startPosY,50,50,BLACK),
                Text(250,startPosY+5,800,50,40,answer.getAnswer()),   
                answer
            });

        startPosY += 100;
    }
}

void QuestionView::update()
{
    Mouse mouse = System::getMouseState();

    for (auto& buttonText : buttonsAnswer)
    {
        if (buttonText.button.Click(mouse))
        {
            INFO(buttonText.answer.getAnswer());
            this->selected = &buttonText;
            testCommit.setAnswerForQuestion(buttonText.answer);
            if (testCommit.getNextQuestion())
            {
                System::getInstance()->setView(new QuestionView(testCommit));
            }
            else System::getInstance()->setMenuView();
        }
    }
}

void QuestionView::render()
{
    questionText.DrawText();
    for (auto &buttonText : buttonsAnswer)
    {
        buttonText.button.DrawButton();
        buttonText.text.DrawText();
    }
}
