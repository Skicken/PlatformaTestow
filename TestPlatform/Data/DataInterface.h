#pragma once
#include "users/user.h"
#include "TestData/Test.h"
#include "users/user.h"
namespace ExternalData
{
	class DataInterface
	{
	public:
		virtual std::vector<Test> getAllTests() = 0;
		virtual std::vector<Test> getTeacherTests(std::string OWNER_ID) = 0;

		virtual void modifyTest(Test& test) = 0;
		virtual void deleteTest(Test& test) = 0;
		virtual void addTest(Test& test,std::string OWNER_ID) = 0;

		virtual User* getUser(std::string login, std::string password) = 0;
		virtual void addUser(User& user, std::string login, std::string password) = 0;
		virtual void deleteUser(User& user) = 0;
		virtual void modifyUser(User& user, std::string login, std::string password) = 0;
		virtual void modifyUser(User& user) = 0;

		virtual std::vector<Test> getStudentAvailableTest(std::string STUDENT_ID) = 0;
		virtual void commitTestResult() = 0;
		virtual void getResults(User& user) = 0;

		/*virtual std::map<std::string, std::string> getCorrectAnswers(std::string TEST_ID);*/
	};
}