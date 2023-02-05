#pragma once
#include "../View.h"
#include <System.h>
#include "TestView.h"

class StudentMenu :
    public View
{

	public:
	    virtual void update() override;
	    virtual void render() override;
	    StudentMenu();
	private:
    bool testsButton = false;
    bool homeworkButton = false;
    bool sendMailButton = false;
    bool logoutButton = false;

    Rectangle layoutRecs[4] = {
        { 24, 144, 240, 48 },
        { 336, 144, 240, 48 },
        { 648, 144, 240, 48 },
        { 1440, 144, 240, 48 },
    };

        

};