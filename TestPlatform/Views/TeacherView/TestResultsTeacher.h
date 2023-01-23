#pragma once
#include "Views/View.h"

class TestResultsTeacher : public View
{

	public:
	void update() override;
	void render() override;
	TestResultsTeacher();

	private:
        int ListView000ScrollIndex = 0;
        int ListView000Active = 0;
        bool Button001Pressed = false;
        int ListView002ScrollIndex = 0;
        int ListView002Active = 0;
        int ListView003ScrollIndex = 0;
        int ListView003Active = 0;
		std::vector<Group> groups;
		std::vector<User> groupUsers;
		std::vector<TestCommit> userCommits;

		bool groupSelected = true;
		bool userSelected = true;

		Rectangle layoutRecs[4] = {
	        { 104, 120, 336, 768 },
	        { 48, 24, 240, 48 },
	        { 552, 120, 336, 768 },
	        { 1032, 120, 336, 768 },
	    };

};  


