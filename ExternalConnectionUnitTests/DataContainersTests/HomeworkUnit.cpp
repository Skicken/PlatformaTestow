#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//Units tests should be run only in release mode.
namespace UnitTests
{

	TEST_CLASS(HOMEWORK)
	{

		TEST_METHOD(HomeworkAddDelete)
		{
			std::string message;
			try {
				MySQL* data = new MySQL();
				Homework homework("What is 2+2?");
				Group group = data->getAllGroups()[0];
				data->addHomework(group, homework);
				std::vector<Homework> dataHomework = data->getAllHomework();
				Assert::IsFalse(dataHomework.empty());
				Assert::AreEqual(std::string("What is 2+2?"), dataHomework[0].getQuestion());
				Assert::IsFalse(dataHomework[0].getID().empty());

				data->deleteHomework(dataHomework[0]);
				dataHomework = data->getAllHomework();
				Assert::IsTrue(dataHomework.empty());
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}
		TEST_METHOD(HomeworkCommitAddDelete)
		{
			std::string message;
			try {
				MySQL* data = new MySQL();
				Homework homework("What is 2+2?");
				Group group = data->getAllGroups()[0];
				data->addHomework(group, homework);
				std::vector<Homework> dataHomework = data->getAllHomework();

				Assert::IsFalse(dataHomework.empty());
				Assert::AreEqual(std::string("What is 2+2?"), dataHomework[0].getQuestion());
				Assert::IsFalse(dataHomework[0].getID().empty());

				HomeworkCommit commit(dataHomework[0], "I think it is 4");

				std::shared_ptr<User> user = data->getUser("user", "root");
				data->commitHomework(user->getID(), commit);
				std::vector<HomeworkCommit> dataCommit = data->getCommitHomework(user->getID());

				Assert::IsFalse(dataCommit.empty());
				Assert::AreEqual(std::string("I think it is 4"), dataCommit[0].getAnswer());
				Assert::IsFalse(dataCommit[0].getID().empty());

				dataCommit = data->getCommitHomework(dataHomework[0]);
				Assert::IsFalse(dataCommit.empty());
				Assert::AreEqual(std::string("I think it is 4"), dataCommit[0].getAnswer());
				Assert::IsFalse(dataCommit[0].getID().empty());



				data->deleteHomework(dataHomework[0]);
				dataHomework = data->getAllHomework();
				Assert::IsTrue(dataHomework.empty());

				dataCommit = data->getCommitHomework(user->getID());
				Assert::IsTrue(dataHomework.empty());


			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}


	};

}
