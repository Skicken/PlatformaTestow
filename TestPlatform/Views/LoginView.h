#pragma once
#include "View.h"
#include "System.h"

class LoginView:
	public View
{
	public:
	void update() override;
	void render() override;
	LoginView();
	private:
	bool showIncorrect;
	std::string errorMessage;
    bool Button001Pressed = false;
    bool TextBox001EditMode = false;
    char TextBox001Text[128] = "";
    bool TextBox002EditMode = false;
    char TextBox002Text[128] = "";

    Rectangle layoutRecs[5] = {
	    {768, 644, 240, 48},
		{744, 524, 288, 24},
    	{744, 572, 288, 24},
		{744, 500, 120, 24},
        {744, 548, 120, 24},
    };
};

