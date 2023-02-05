#pragma once
#include "Views/View.h"
#include "Views/TeacherView/TeacherView.h"

class AdminView :
    public TeacherMenu
{
	public:
	void update() override;
	void render() override;
	private:
	Rectangle manageUsersRect{ 24, 220, 240, 48 };
	bool manageUsersButton = false;


};

