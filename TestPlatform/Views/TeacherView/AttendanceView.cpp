#include "ptpch.h"
#include "AttendanceView.h"
#include <raygui.h>

#include "System.h"

AttendanceView::AttendanceView()
{
    refreshData();
}

void AttendanceView::update()
{
    if(Button007Pressed)
    {
        System::getInstance()->setMenuView();
    }
    if(Button004Pressed && isGroupSelected && newAttendanceList==nullptr)
    {
        newAttendanceList = std::make_unique<AttendanceList>(groups[ListView000Active], System::getDataInterface()->getCurrentDate());
        attendanceLists.push_back(*newAttendanceList);
        ListView001Active = attendanceLists.size()-1;
    }
    if(Button005Pressed && ListView002Active >= 0 && ListView002Active < groupUsers.size())
    {
        attendanceLists[ListView001Active].setUserPresent(
            groupUsers[ListView002Active]
        );
    }
    if (Button006Pressed && ListView003Active >= 0 && ListView003Active < attendanceLists[ListView001Active].getPresentUsers().size())
    {
        attendanceLists[ListView001Active].removeUserPresent(
            attendanceLists[ListView001Active].getPresentUsers()[ListView003Active]
        );
    }
    if(Button008Pressed && isDateSelected && isGroupSelected)
    {
        try {
            System::getDataInterface()->addAttendanceList(attendanceLists[ListView001Active]);
        }
        catch(ExternalData::DatabaseException &exception)
        {
	        if(exception.getType()==ExternalData::ExceptionType::ENTRY_EXISTS)
	        {
                System::getDataInterface()->deleteAttendanceList(attendanceLists[ListView001Active]);
                System::getDataInterface()->addAttendanceList(attendanceLists[ListView001Active]);
	        }
        }
        refreshData();
    }

}

void AttendanceView::render()
{
    lastGroup = ListView000Active;
    ListView000Active = GuiListView(layoutRecs[0], 
        Helper::ListToStringSeparated(groups,&Group::getName).c_str()
        , &ListView000ScrollIndex, ListView000Active);

    isGroupSelected = ListView000Active >= 0 && ListView000Active < groups.size();
    if(lastGroup!= ListView000Active && isGroupSelected)
    {
        attendanceLists = System::getDataInterface()->getGroupAttendanceList(groups[ListView000Active]);
    }

    auto lambda = [](AttendanceList & list)
    {
        return list.getDate();
    };
    if(isGroupSelected)
    ListView001Active = GuiListView(layoutRecs[1], 
        Helper::ListToStringSeparated(attendanceLists, lambda).c_str(), &ListView001ScrollIndex, ListView001Active);
    isDateSelected = ListView001Active >= 0 && ListView001Active < attendanceLists.size();
    auto lambda1 = [](User& user)
    {
        return user.getName()+" "+user.getSurname();
    };

    if(isDateSelected && isGroupSelected)
    {

        groupUsers = attendanceLists[ListView001Active].getGroup().getUsers();
        ListView002Active = GuiListView(layoutRecs[2], 
            Helper::ListToStringSeparated(groupUsers,lambda1).c_str()

            , &ListView002ScrollIndex, ListView002Active);
    }
    if (isDateSelected && isGroupSelected)
    {
        AttendanceList list = attendanceLists[ListView001Active];
        std::vector<User> presentUsers = list.getPresentUsers();
        ListView003Active = GuiListView(layoutRecs[3], Helper::ListToStringSeparated(presentUsers, lambda1).c_str()
            , &ListView003ScrollIndex, ListView003Active);
    }
    Button004Pressed = GuiButton(layoutRecs[4], "New Attendance List");
    Button005Pressed = GuiButton(layoutRecs[5], "Add to present");
    Button006Pressed = GuiButton(layoutRecs[6], "Remove from present");
    Button007Pressed = GuiButton(layoutRecs[7], "Menu");
    Button008Pressed = GuiButton({ 1536, 768, 216, 40 }, "Commit AttentanceList");


}

void AttendanceView::refreshData()
{
    groups = System::getDataInterface()->getAllGroups();
    attendanceLists = System::getDataInterface()->getGroupAttendanceList(groups[ListView000Active]);
    groupUsers = groups[ListView000Active].getUsers();

}
