#include "pch.h"


//Units tests should be run only in release mode.
namespace UnitTests
{
	TEST_CLASS(TESTS)
	{
		TEST_METHOD(GetExampleTest)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();
				std::vector<Test> test = data->getAllTests();
				Assert::IsTrue(test.size() > 0);
				Assert::IsTrue(test[0].getQuestions().size() > 0);
				Assert::IsTrue(test[0].getQuestions()[0].getAnswers().size() > 0);
				Test& t = test[0];
				Assert::AreEqual(t.getTestName(), std::string("Example Test"));
				delete data;
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}

		TEST_METHOD(GetTeacherTest)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();
				std::shared_ptr<User> user = data->getUser("user", "user");



				std::vector<Test> test = data->getTeacherTests(user->getID());
				Assert::IsTrue(test.size() > 0);
				Assert::IsTrue(test[0].getQuestions().size() > 0);
				Assert::IsTrue(test[0].getQuestions()[0].getAnswers().size() > 0);
				Assert::AreEqual(test[0].getQuestions()[0].getCorrectAnswer().getAnswer(), std::string("tak"));
				Test& t = test[0];
				Assert::AreEqual(t.getTestName(), std::string("Example Test"));
				delete data;
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}
		TEST_METHOD(GetAssignedTests)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();
				std::shared_ptr<User> user = data->getUser("admin", "admin");
				std::vector<Test> test = data->getStudentAvailableTest(user->getID());
				Assert::IsTrue(test.size() > 0);
				Assert::IsTrue(test[0].getQuestions().size() > 0);
				Assert::IsTrue(test[0].getQuestions()[0].getAnswers().size() > 0);
				Test& t = test[0];
				Assert::AreEqual(t.getTestName(), std::string("Example Test"));
				delete data;
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}
		TEST_METHOD(TestAddModifyDelete)
		{
			std::string message;
			try {
				DataInterface* data = new MySQL();
				std::shared_ptr<User> user = data->getUser("admin", "admin");
				std::vector<Question> questions;
				questions.push_back(Question("Do you like hamburgers?", { "Yes","No" }, std::string("Yes")));
				Test test("Test", "blabla", false, questions);
				data->addTest(test, user->getID());

				std::vector<Test> tests = data->getTeacherTests(user->getID());

				Assert::IsTrue(tests.size() > 0);
				Test* testFrom = nullptr;
				for (auto test : tests)
				{
					if (test.getTestName() == "Test")
					{
						testFrom = new Test(test);
					}
				}
				Assert::IsNotNull(testFrom);
				Assert::IsTrue(testFrom->getQuestions().size() > 0);
				Assert::IsTrue(testFrom->getQuestions()[0].getAnswers().size() > 1);
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
			catch (DatabaseException& e)
			{
				message = std::string(e.what());
			}
			failMessage(message);
		}
		TEST_METHOD(TestResultAddDelete)
		{
			std::string message;
			try {
				MySQL* data = new MySQL();
				std::vector<Test> tests = data->getAllTests();
				Test test = tests[0];
				TestCommit result(test);
				Question q = result.getCurrentQuestion();
				result.setAnswerForQuestion(q.getAnswers()[0]);
				std::shared_ptr<User> user = data->getUser("admin", "admin");
				data->commitTestResult(result, user->getID());
				TestCommit dataResult = data->getTestResults(user->getID())[0];

				Assert::IsFalse(dataResult.getTest().getQuestions().empty());
				Assert::IsFalse(dataResult.getQuestionAnswer().empty());
				Assert::AreEqual(std::string("Example Test"), dataResult.getTest().getTestName());

				data->deleteTestResult(dataResult);
				std::vector<TestCommit> results = data->getTestResults(user->getID());
				Assert::IsTrue(results.empty());
			}
			catch (DatabaseException& e)
			{
				message = std::string(e.what());

			}
			failMessage(message);
		}


	};
}