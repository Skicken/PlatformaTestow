#pragma once
#include "ptpch.h"
#include "Views/View.h"

class QuestionView: public View
{
public:
	QuestionView(std::shared_ptr<TestCommit> commit, bool preview);

	QuestionView(std::shared_ptr<TestCommit> commit);

	void goToPreviousQuestion();
	virtual void update() override;
	virtual void render() override;
	private:
	std::shared_ptr<TestCommit> testCommit;
    void goToNextQuestion();

    Question&  currentQuestion;
    float progressBarValue = 0.0f;
    bool nextQuestionButton = false;
    bool previousQuestionButton = false;
    int selectedAnswerIndex = 0;
    bool selectedAnswer = false;

    int ListView005ScrollIndex = 0;

    bool preview = false;

    const Rectangle StartRectangle{ 288, 288, 24, 24 };
    Rectangle layoutRecs[5] = {
        { 144, 840, 1584, 48 },
        { 1440, 744, 288, 48 },
        { 144, 816, 120, 24 },
        { 144, 744, 288, 48 },
        { 432, 288, 1008, 432 }
    };

};

