#pragma once
#include "Views/View.h"
#include "System.h"
#include "Utilities/Helper.h"

class TestView:public View
{
public:
	TestView();

	void update() override;
	void render() override;

	private:
    std::vector<Test> availableTests;
    std::vector<TestCommit> commitedTests;
    std::string availableTestString;
    std::string commitedTestString;
    void refresh();

    int ListView000ScrollIndex = 0;
    int ListView000Active = 0;
    bool Button001Pressed = false;
    int ListView002ScrollIndex = 0;
    int ListView002Active = 0;
    bool Button004Pressed = false;
    bool Button005Pressed = false;

    Rectangle layoutRecs[5] = {
        { 160, 168, 656, 600 },
        { 24, 48, 216, 48 },
        { 1080, 168, 656, 600 },
        { 160, 792, 240, 48 },
        { 1080, 792, 240, 48 },
    };
};

