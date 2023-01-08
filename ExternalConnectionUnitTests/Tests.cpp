#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//Units tests should be run only in release mode.
namespace UnitTests
{
	using namespace ExternalData;
	TEST_CLASS(MYSQL_ATTENDANCE)
	{
		TEST_METHOD(getExampleGroup)
		{
			try {
				DataInterface* data = new MySQL();
				std::vector<Group> groups = data->getAllGroups();
				Assert::IsTrue(groups.size() > 0);
				Assert::AreEqual(std::string("5B"), groups[0].getName());
				Assert::IsTrue(groups[0].getUsers().size() > 0);
				Assert::AreEqual(std::string("Nowak"), groups[0].getUsers()[0].getSurname());
			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}
		}
		TEST_METHOD(testUniqueID)
		{
			try {
				MySQL* data = new MySQL();
				for (int i = 0; i < 10; i++)
				{
					std::string ID = data->getUniqueID();
					Assert::AreNotEqual(std::string(""), ID);
				}
			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}
		}
		TEST_METHOD(groupDA)
		{
			try {
				DataInterface* data = new MySQL();
				std::vector<User> users = data->getAllUsers();
				Group addGroup("bak", users);
				data->addGroup(addGroup);
				std::vector<Group> groups = data->getAllGroups();
				Group* test = nullptr;
				for(auto &group:groups)
				{
					if(group.getName()=="bak")
					{
						test = &group;
					}
				}
				Assert::IsNotNull(test);
				Assert::IsTrue(test->getUsers().size() > 1);
				data->deleteGroup(*test);

			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}
		}
		TEST_METHOD(getExampleAttendance)
		{
			try {
				DataInterface* data = new MySQL();
				std::vector<Group> groups = data->getAllGroups();
				std::string date = "2023-01-06";
				AttendanceList attend = data->getAttendanceList(groups[0], date);
				Assert::IsFalse(attend.getPresentUsers().empty());
				Assert::AreEqual(std::string("Nowak"),attend.getPresentUsers()[0].getSurname() );
			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}

		}

		TEST_METHOD(AttendanceListDA)
		{
			try {
				MySQL* data = new MySQL();
				std::vector<Group> groups = data->getAllGroups();
				Group group = groups[0];
				AttendanceList list(group);
				std::string date = data->getCurrentDate();
				for(auto user:groups[0].getUsers())
				{
					list.setUserPresent(user);
				}
				data->addAttendanceList(list);
				AttendanceList attend = data->getAttendanceList(group,date);
				Assert::IsFalse(attend.getPresentUsers().empty());
				data->deleteAttendanceList(attend);
				attend = data->getAttendanceList(group, date);
				Assert::IsTrue(attend.getPresentUsers().empty());

			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}
		}

		TEST_METHOD(TestResultDA)
		{
			try {
				MySQL* data = new MySQL();
				std::vector<Test> tests = data->getAllTests();
				Test test = tests[0];
				TestCommit result(test);
				Question q =  result.getCurrentQuestion();
				result.setAnswerForQuestion(q.getAnswers()[0]);
				User* user = data->getUser("admin", "admin");
				data->commitTestResult(result, user->getID());
				TestCommit dataResult = data->getTestResults(user->getID())[0];

				Assert::IsFalse(dataResult.getTest().getQuestions().empty());
				Assert::IsFalse(dataResult.getQuestionAnswer().empty());
				Assert::AreEqual(std::string("Example Test"), dataResult.getTest().getTestName());

				data->deleteTestResult(dataResult);
				std::vector<TestCommit> results = data->getTestResults(user->getID());
				Assert::IsTrue(results.empty());
			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}
		}

		TEST_METHOD(HomeworkDA)
		{
			try {
				MySQL* data = new MySQL();
				Homework homework("What is 2+2?");
				Group group = data->getAllGroups()[0];
				data->addHomework(group, homework);
				std::vector<Homework> dataHomework = data->getAllHomeworks();
				Assert::IsFalse(dataHomework.empty());
				Assert::AreEqual(std::string("What is 2+2?"), dataHomework[0].getQuestion());
				Assert::IsFalse(dataHomework[0].getID().empty());

				data->deleteHomework(dataHomework[0]);
				dataHomework = data->getAllHomeworks();
				Assert::IsTrue(dataHomework.empty());
			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}
		}
		TEST_METHOD(HomeworkCommitDA)
		{
			try {
				MySQL* data = new MySQL();
				Homework homework("What is 2+2?");
				Group group = data->getAllGroups()[0];
				data->addHomework(group, homework);
				std::vector<Homework> dataHomework = data->getAllHomeworks();

				Assert::IsFalse(dataHomework.empty());
				Assert::AreEqual(std::string("What is 2+2?"), dataHomework[0].getQuestion());
				Assert::IsFalse(dataHomework[0].getID().empty());

				HomeworkCommit commit(dataHomework[0], "I think it is 4");

				User* user = data->getUser("user", "root");
				data->commitHomework(user->getID(), commit);
				std::vector<HomeworkCommit> dataCommit = data->getCommitedHomeworks(user->getID());

				Assert::IsFalse(dataCommit.empty());
				Assert::AreEqual(std::string("I think it is 4"), dataCommit[0].getAnswer());
				Assert::IsFalse(dataCommit[0].getID().empty());

				dataCommit = data->getCommitedHomeworks(dataHomework[0]);
				Assert::IsFalse(dataCommit.empty());
				Assert::AreEqual(std::string("I think it is 4"), dataCommit[0].getAnswer());
				Assert::IsFalse(dataCommit[0].getID().empty());



				data->deleteHomework(dataHomework[0]);
				dataHomework = data->getAllHomeworks();
				Assert::IsTrue(dataHomework.empty());

				dataCommit = data->getCommitedHomeworks(user->getID());
				Assert::IsTrue(dataHomework.empty());


			}
			catch (sql::SQLException& e)
			{
				std::string message = std::string(e.what());
				Logger::WriteMessage(message.c_str());
				Assert::Fail();

			}
		}


	};

}
