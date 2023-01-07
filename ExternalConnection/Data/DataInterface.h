#pragma once
#include "TestData/AttendanceList.h"
#include "TestData/Groups.h"
#include "users/user.h"
#include "TestData/Test.h"
#include "TestData/TestResult.h"
#include "users/teacher.h"
#include "users/Admin.h"

namespace ExternalData
{
	
	class DataInterface
	{
		public:

			 /**
			 * \return All tests available in database
			 */
			virtual std::vector<Test> getAllTests() = 0;
			virtual std::vector<Test> getTeacherTests(std::string OWNER_ID) = 0;

			virtual std::vector<Test> getStudentAvailableTest(std::string STUDENT_ID) = 0;

			virtual void modifyTest(Test& test, std::string OWNER_ID) = 0;
			virtual void deleteTest(Test& test) = 0;
			virtual void addTest(Test& test,std::string OWNER_ID) = 0;

			virtual std::vector<User> getAllUsers() = 0;
			virtual User* getUser(std::string login, std::string password) = 0;
			virtual void addUser(User& user, std::string login, std::string password) = 0;
			virtual void deleteUser(User& user) = 0;
			virtual void modifyUser(User& user, std::string login, std::string password) = 0;
			virtual void modifyUser(User& user) = 0;

			virtual void addTestResult(TestResult& result,std::string STUDENT_ID)=0;
			virtual std::vector<TestResult> getTestResults(std::string STUDENT_ID) = 0;

			virtual void addGroup(Group& group) = 0;
			virtual std::vector<Group> getAllGroups() = 0;
			virtual void deleteGroup(Group& group) = 0;

			virtual void addAttendanceList(AttendanceList& list) = 0;
			virtual void deleteAttendanceList(AttendanceList& list) = 0;
			virtual std::vector<AttendanceList> getAllAttendanceLists() = 0;
			
		/*virtual std::map<std::string, std::string> getCorrectAnswers(std::string TEST_ID);*/
	};
}
