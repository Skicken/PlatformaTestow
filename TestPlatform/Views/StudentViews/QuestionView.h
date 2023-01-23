#pragma once
#include "ptpch.h"
#include "Views/View.h"

class QuestionView: public View
{
public:
	QuestionView(std::shared_ptr<TestCommit> commit, bool preview);

	QuestionView(std::shared_ptr<TestCommit> commit);

	virtual void update() override;
	virtual void render() override;
	private:
	std::shared_ptr<TestCommit> testCommit;

    float ProgressBar000Value = 0.0f;
    bool Button002Pressed = false;
    bool Button004Pressed = false;
    int ListView005ScrollIndex = 0;
    int ListView005Active = 0;

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

