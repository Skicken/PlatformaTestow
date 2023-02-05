#pragma once
#include "../View.h"
class AttendanceView :
    public View
{

	public:
	    AttendanceView();
	    void refreshData();
	    void update() override;
		void render() override;
	private:
	    std::vector<AttendanceList> attendanceLists;
	    std::vector<Group> groups;
	    std::vector<User> groupUsers;
	    std::unique_ptr<AttendanceList> newAttendanceList = nullptr;

		bool groupSelected = true;
	    bool dateSelected = true;
	    int selectedGroupIndex = 0;
	    int selectedAttendanceListIndex = 0;
	    int selectedUserIndex = 0;
	    int selectedPresentUserIndex = 0;
	    bool addAttendanceListButton = false;
	    bool addUserToPresentButton = false;
	    bool removeUserFromPresentButton = false;
	    bool menuButton = false;
	    bool commitAttendanceButton = false;

	    int lastGroup = 0;
	    Rectangle layoutRecs[8] = {
	        { 72, 144, 303, 613 },
	        { 440, 144, 303, 613 },
	        { 824, 144, 303, 613 },
	        { 1192, 144, 303, 613 },
	        { 480, 768, 216, 40 },
	        { 864, 768, 216, 40 },
	        { 1240, 768, 216, 40 },
	        { 24, 48, 216, 48 },
	    };


	    int ListView000ScrollIndex = 0;
	    int ListView001ScrollIndex = 0;
	    int ListView002ScrollIndex = 0;
	    int ListView003ScrollIndex = 0;


		

};

