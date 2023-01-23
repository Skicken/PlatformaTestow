#pragma once
#include "../View.h"
class AttendanceView :
    public View
{
	

	public:
    AttendanceView();
    void update() override;
	void render() override;
	private:
        std::vector<AttendanceList> attendanceLists;
        std::vector<Group> groups;
        std::vector<User> groupUsers;
        std::unique_ptr<AttendanceList> newAttendanceList = nullptr;

	bool isGroupSelected = true;
    bool isDateSelected = true;

    int ListView000ScrollIndex = 0;
    int ListView000Active = 0;
    int ListView001ScrollIndex = 0;
    int ListView001Active = 0;
    int ListView002ScrollIndex = 0;
    int ListView002Active = 0;
    int ListView003ScrollIndex = 0;
    int ListView003Active = 0;
    bool Button004Pressed = false;
    bool Button005Pressed = false;
    bool Button006Pressed = false;
    bool Button007Pressed = false;
    bool Button008Pressed = false;

    int lastGroup = 0;
    Rectangle layoutRecs[8] = {
        { 72, 144, 303, 613 },
        { 440, 144, 303, 613 },
        { 824, 144, 303, 613 },
        { 1192, 144, 303, 613 },
        { 480, 768, 216, 40 },
        { 864, 768, 216, 40 },
        { 1240, 768, 216, 40 },
        { 72, 24, 208, 48 },
    };
    void refreshData();


		

};

