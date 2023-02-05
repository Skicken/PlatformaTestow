#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//Units tests should be run only in release mode.
namespace UnitTests
{

	TEST_CLASS(GROUP)
	{

		TEST_METHOD(getExampleGroup)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();
				std::vector<Group> groups = data->getAllGroups();
				Assert::IsTrue(groups.size() > 0);
				Assert::AreEqual(std::string("5B"), groups[0].getName());
				Assert::IsTrue(groups[0].getUsers().size() > 0);
				Assert::AreEqual(std::string("Nowak"), groups[0].getUsers()[0].getSurname());
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}
		TEST_METHOD(testUniqueID)
		{
			std::string message;
			try {
				MySQL* data = new MySQL();
				for (int i = 0; i < 10; i++)
				{
					std::string ID = data->getUniqueID();
					Assert::AreNotEqual(std::string(""), ID);
				}
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());

			}
			failMessage(message);

		}
		TEST_METHOD(groupAddDelete)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();
				std::vector<User> users = data->getAllUsers();
				Group addGroup("bak", users);
				data->addGroup(addGroup);
				std::vector<Group> groups = data->getAllGroups();
				Group* test = nullptr;
				for (auto& group : groups)
				{
					if (group.getName() == "bak")
					{
						test = &group;
					}
				}
				Assert::IsNotNull(test);
				Assert::IsTrue(test->getUsers().size() > 1);
				data->deleteGroup(*test);

			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}

	};

}
