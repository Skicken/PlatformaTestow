#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//Units tests should be run only in release mode.
namespace UnitTests
{
	using namespace ExternalData;
	TEST_CLASS(MYSQL_INTERFACE)
	{
			TEST_METHOD(LoginUserExample)
			{
				try
				{
					DataInterface* data = new MySQL();
					User* user = data->getUser("admin", "admin");
					Assert::AreNotEqual(user->getID(), std::string(""));
					Assert::IsNotNull(user);
					Assert::AreEqual(user->getName(), std::string("Jan"));
					Assert::AreEqual(user->getSurname(), std::string("Nowak"));
					Assert::AreEqual(user->getEmail(), std::string("kowalski@gmail.com.pl"));
					Assert::IsTrue(user->getType() == UserType::STUDENT);
					delete user;
					delete data;
				}
				catch (sql::SQLException& e)
				{
					std::string message = std::string(e.what());
					Logger::WriteMessage(message.c_str());
					Assert::Fail();
				}

			}
			TEST_METHOD(UserDAM)
			{
				try {
					DataInterface* data = new MySQL();

					//adding user
					User* user = new Teacher("name", "surname", "name@mail.pl");
					data->addUser(*user, "root", "root");
					delete user;
					user = data->getUser("root", "root");
					Assert::AreNotEqual(user->getID(), std::string(""));
					Assert::IsNotNull(user);
					Assert::AreEqual(user->getName(), std::string("name"));
					Assert::AreEqual(user->getSurname(), std::string("surname"));
					Assert::AreEqual(user->getEmail(), std::string("name@mail.pl"));
					Assert::IsTrue(user->getType() == UserType::TEACHER);
					delete user;

					//modyfing user
					user = data->getUser("root", "root");
					user->setName("Ronald");
					user->setSurname("Reagan");
					user->setType(UserType::ADMIN);
					data->modifyUser(*user, "root1", "root1");
					delete user;

					user = data->getUser("root1", "root1");
					Assert::IsNotNull(user);
					Assert::AreEqual(std::string("Ronald"),user->getName());
					Assert::AreEqual(user->getSurname(), std::string("Reagan"));
					Assert::IsTrue(user->getType() == UserType::ADMIN);
					Assert::AreNotEqual(user->getID(), std::string(""));


					//deleting user
					data->deleteUser(*user);
					Assert::IsNull(data->getUser("root1", "root1"));

					delete user;
					delete data;
				}
				catch (sql::SQLException& e)
				{
					std::string message = std::string(e.what());
					Logger::WriteMessage(message.c_str());
					Assert::Fail();
				}
			}

			TEST_METHOD(GetExampleTest)
			{
				try {
					DataInterface* data = new MySQL();
					std::vector<Test> test = data->getAllTests();
					Assert::IsTrue(test.size()>0);
					Assert::IsTrue(test[0].getQuestions().size() > 0);
					Assert::IsTrue(test[0].getQuestions()[0].getAnswers().size() > 0);
					Test& t = test[0];
					Assert::AreEqual(t.getTestName(), std::string("Example Test"));
					delete data;
				}
				catch (sql::SQLException& e)
				{
					std::string message = std::string(e.what());
					Logger::WriteMessage(message.c_str());
					Assert::Fail();

				}
			}

			TEST_METHOD(GetTeacherTest)
			{
				try {
					DataInterface* data = new MySQL();
					User* user = data->getUser("user", "root");



					std::vector<Test> test = data->getTeacherTests(user->getID());
					Assert::IsTrue(test.size() > 0);
					Assert::IsTrue(test[0].getQuestions().size() > 0);
					Assert::IsTrue(test[0].getQuestions()[0].getAnswers().size() > 0);
					Assert::AreEqual(test[0].getQuestions()[0].getCorrectAnswer().getAnswer(), std::string("tak"));
					Test& t = test[0];
					Assert::AreEqual(t.getTestName(), std::string("Example Test"));
					delete data;
				}
				catch (sql::SQLException& e)
				{
					std::string message = std::string(e.what());
					Logger::WriteMessage(message.c_str());
					Assert::Fail();
				}
			}
			TEST_METHOD(GetAssignedTests)
			{
				try {
					DataInterface* data = new MySQL();
					User* user = data->getUser("admin", "admin");
					std::vector<Test> test = data->getStudentAvailableTest(user->getID());
					Assert::IsTrue(test.size() > 0);
					Assert::IsTrue(test[0].getQuestions().size() > 0);
					Assert::IsTrue(test[0].getQuestions()[0].getAnswers().size() > 0);
					Test& t = test[0];
					Assert::AreEqual(t.getTestName(), std::string("Example Test"));
					delete data;
				}
				catch (sql::SQLException& e)
				{
					std::string message = std::string(e.what());
					Logger::WriteMessage(message.c_str());
					Assert::Fail();
				}
			}
			TEST_METHOD(TestDAM)
			{
				try {
					DataInterface* data = new MySQL();
					User* user = data->getUser("admin", "admin");
					std::vector<Question> questions;
					questions.push_back(Question("Do you like hamburgers?", { "Yes","No" }, std::string("Yes")));
					Test test("Test", "blabla", false, questions);
					data->addTest(test, user->getID());

					std::vector<Test> tests = data->getTeacherTests(user->getID());

					Assert::IsTrue(tests.size() > 0);
					Test* testFrom = nullptr;
					for(auto test:tests)
					{
						if(test.getTestName()=="Test")
						{
							testFrom = new Test(test);
						}
					}
					Assert::IsNotNull(testFrom);
					Assert::IsTrue(testFrom->getQuestions().size() > 0);
					Assert::IsTrue(testFrom->getQuestions()[0].getAnswers().size()> 1);
					Assert::AreNotEqual(testFrom->getQuestions()[0].getCorrectAnswer().getAnswer(), std::string(""));

					testFrom->setTestName("New life!");
					testFrom->getQuestions()[0].setQuestion("Do you like french fries?");

					data->modifyTest(*testFrom, user->getID());

					tests = data->getTeacherTests(user->getID());
					Assert::IsTrue(tests.size() > 0);
					testFrom = new Test(tests[0]);
		
					Assert::IsNotNull(testFrom);
					Assert::IsTrue(testFrom->getQuestions().size() > 0);
					Assert::IsTrue(testFrom->getQuestions()[0].getAnswers().size() > 1);
					Assert::AreEqual(testFrom->getQuestions()[0].getQuestionName(), std::string("Do you like french fries?"));

					data->deleteTest(*testFrom);
					tests = data->getTeacherTests(user->getID());
					Assert::IsTrue(tests.size() == 0);

					delete data;
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
