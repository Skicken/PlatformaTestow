#include "ptpch.h"
#include "AttendanceView.h"
#include <raygui.h>

#include "System.h"
#include "Utilities/ClassToStringFormatter.h"

AttendanceView::AttendanceView()
{
    refreshData();
}

void AttendanceView::update()
{
    if(menuButton)
    {
        System::getInstance()->setMenuView();
    }
    if(addAttendanceListButton && groupSelected && newAttendanceList==nullptr)
    {
        newAttendanceList = std::make_unique<AttendanceList>(groups[selectedGroupIndex], System::getDataInterface()->getCurrentDate());
        attendanceLists.push_back(*newAttendanceList);
        selectedAttendanceListIndex = attendanceLists.size()-1;
    }
    if(addUserToPresentButton && selectedUserIndex >= 0 && selectedUserIndex < groupUsers.size())
    {
        attendanceLists[selectedAttendanceListIndex].setUserPresent(
            groupUsers[selectedUserIndex]
        );
    }
    if (removeUserFromPresentButton && selectedPresentUserIndex >= 0 && selectedPresentUserIndex < attendanceLists[selectedAttendanceListIndex].getPresentUsers().size())
    {
        attendanceLists[selectedAttendanceListIndex].removeUserPresent(
            attendanceLists[selectedAttendanceListIndex].getPresentUsers()[selectedPresentUserIndex]
        );
    }
    if(commitAttendanceButton && dateSelected && groupSelected)
    {
        try {
            System::getDataInterface()->addAttendanceList(attendanceLists[selectedAttendanceListIndex]);
        }
        catch(ExternalData::DatabaseException &exception)
        {
	        if(exception.getType()==ExternalData::ExceptionType::ENTRY_EXISTS)
	        {
                System::getDataInterface()->deleteAttendanceList(attendanceLists[selectedAttendanceListIndex]);
                System::getDataInterface()->addAttendanceList(attendanceLists[selectedAttendanceListIndex]);
	        }
        }
        refreshData();
    }

}

void AttendanceView::render()
{
    lastGroup = selectedGroupIndex;
    selectedGroupIndex = GuiListView(layoutRecs[0], 
        Helper::ListToStringSeparated(groups,&Group::getName).c_str()
        , &ListView000ScrollIndex, selectedGroupIndex);

    groupSelected = selectedGroupIndex >= 0 && selectedGroupIndex < groups.size();
    if(lastGroup!= selectedGroupIndex && groupSelected)
    {
        attendanceLists = System::getDataInterface()->getGroupAttendanceList(groups[selectedGroupIndex]);
    }

    if(groupSelected)
    selectedAttendanceListIndex = GuiListView(layoutRecs[1], 
        Helper::ListToStringSeparated(attendanceLists, ClassToStringFormatter::attendanceListToString).c_str(), &ListView001ScrollIndex, selectedAttendanceListIndex);
    dateSelected = selectedAttendanceListIndex >= 0 && selectedAttendanceListIndex < attendanceLists.size();


    if(dateSelected && groupSelected)
    {

        groupUsers = attendanceLists[selectedAttendanceListIndex].getGroup().getUsers();
        selectedUserIndex = GuiListView(layoutRecs[2], 
            Helper::ListToStringSeparated(groupUsers,ClassToStringFormatter::userToString).c_str()

            , &ListView002ScrollIndex, selectedUserIndex);
    }
    if (dateSelected && groupSelected)
    {
        AttendanceList list = attendanceLists[selectedAttendanceListIndex];
        std::vector<User> presentUsers = list.getPresentUsers();
        selectedPresentUserIndex = GuiListView(layoutRecs[3], Helper::ListToStringSeparated(presentUsers, ClassToStringFormatter::userToString).c_str()
            , &ListView003ScrollIndex, selectedPresentUserIndex);
    }
    addAttendanceListButton = GuiButton(layoutRecs[4], "New Attendance List");
    addUserToPresentButton = GuiButton(layoutRecs[5], "Add to present");
    removeUserFromPresentButton = GuiButton(layoutRecs[6], "Remove from present");
    menuButton = GuiButton(layoutRecs[7], "Menu");
    commitAttendanceButton = GuiButton({ 1536, 768, 216, 40 }, "Commit AttentanceList");


}

void AttendanceView::refreshData()
{
    groups = System::getDataInterface()->getAllGroups();
    attendanceLists = System::getDataInterface()->getGroupAttendanceList(groups[selectedGroupIndex]);
    groupUsers = groups[selectedGroupIndex].getUsers();

}
