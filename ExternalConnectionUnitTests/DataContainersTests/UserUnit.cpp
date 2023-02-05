#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//Units tests should be run only in release mode.
namespace UnitTests
{
	TEST_CLASS(USER)
	{
		TEST_METHOD(LoginUserExample)
		{
			std::string message;
			try
			{
				DataInterface* data = new MySQL();
				std::shared_ptr<User> user = data->getUser("admin", "admin");
				Assert::AreNotEqual(user->getID(), std::string(""));
				Assert::IsTrue(user != nullptr);
				Assert::AreEqual(user->getName(), std::string("Jan"));
				Assert::AreEqual(user->getSurname(), std::string("Nowak"));
				Assert::AreEqual(user->getEmail(), std::string("test123abe@gmail.com"));
				Assert::IsTrue(user->getType() == UserType::STUDENT);

				delete data;
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);

		}
		TEST_METHOD(UserAddModifyDelete)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();

				//adding user
				std::shared_ptr<User> user = std::shared_ptr<User>{new User("name", "surname", "name@mail.pl",UserType::TEACHER) };
				data->addUser(*user, "root", "root");
				user = data->getUser("root", "root");
				Assert::AreNotEqual(user->getID(), std::string(""));
				Assert::IsTrue(user!=nullptr);
				Assert::AreEqual(user->getName(), std::string("name"));
				Assert::AreEqual(user->getSurname(), std::string("surname"));
				Assert::AreEqual(user->getEmail(), std::string("name@mail.pl"));
				Assert::IsTrue(user->getType() == UserType::TEACHER);

				//modyfing user
				user = data->getUser("root", "root");
				user->setName("Ronald");
				user->setSurname("Reagan");
				user->setType(UserType::ADMIN);
				data->modifyUser(*user, "root1", "root1");

				user = data->getUser("root1", "root1");
				Assert::IsTrue(user != nullptr);
				Assert::AreEqual(std::string("Ronald"), user->getName());
				Assert::AreEqual(user->getSurname(), std::string("Reagan"));
				Assert::IsTrue(user->getType() == UserType::ADMIN);
				Assert::AreNotEqual(user->getID(), std::string(""));


				//deleting user
				data->deleteUser(*user);
				Assert::IsFalse(data->getUser("root1", "root1")!=nullptr);

				delete data;
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);

		}

	};

}
