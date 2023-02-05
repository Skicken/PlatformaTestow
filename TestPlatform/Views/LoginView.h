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
    bool loginButton = false;
    bool loginEdit = false;
    char loginInput[128] = "";
    bool passwordEdit = false;
    char passwordInput[128] = "";

    Rectangle layoutRecs[5] = {
	    {768, 644, 240, 48},
		{744, 524, 288, 24},
    	{744, 572, 288, 24},
		{744, 500, 120, 24},
        {744, 548, 120, 24},
    };
};

