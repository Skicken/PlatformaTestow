#pragma once
#include "View.h"
#include "System.h"
#include <UI/Button.h>
#include <UI/Text.h>
class LoginView:
	public View
{
	public:
	void update() override;
	void render() override;
	LoginView();
	private:
		Button loginButton;
		Text loginInfoText;
		Text login;
		Text password;

		Text incorrect;
		bool showIncorrect;

};

