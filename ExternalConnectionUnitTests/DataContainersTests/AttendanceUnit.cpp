#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//Units tests should be run only in release mode.
namespace UnitTests
{

	TEST_CLASS(MYSQL_ATTENDANCE)
	{

		TEST_METHOD(getExampleAttendance)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();
				std::vector<Group> groups = data->getAllGroups();
				std::string date = "2023-01-06";
				AttendanceList attend = data->getAttendanceList(groups[0], date);
				Assert::IsFalse(attend.getPresentUsers().empty());
				Assert::AreEqual(std::string("Nowak"), attend.getPresentUsers()[0].getSurname());
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}

		TEST_METHOD(AttendanceListAddDelete)
		{
			std::string message;
			try {
				MySQL* data = new MySQL();
				std::vector<Group> groups = data->getAllGroups();
				Group group = groups[0];
				AttendanceList list(group);
				std::string date = data->getCurrentDate();
				for (auto user : groups[0].getUsers())
				{
					list.setUserPresent(user);
				}
				data->addAttendanceList(list);
				AttendanceList attend = data->getAttendanceList(group, date);
				Assert::IsFalse(attend.getPresentUsers().empty());
				data->deleteAttendanceList(attend);
				attend = data->getAttendanceList(group, date);
				Assert::IsTrue(attend.getPresentUsers().empty());

			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}


	};

}
