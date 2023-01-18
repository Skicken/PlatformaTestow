#pragma once
#include "ptpch.h"
#include "View.h"
#include <UI/Button.h>
#include <UI/Text.h>
class QuestionView: public View
{
	public:
	QuestionView(TestCommit& commit);
	virtual void update() override;
	virtual void render() override;
	private:
	TestCommit testCommit;
	Text questionText;
	struct ButtonAnswer{
		Button button;
		Text text;
		Answer answer;
	};
	ButtonAnswer* selected = nullptr;
	std::vector<ButtonAnswer> buttonsAnswer;
};

