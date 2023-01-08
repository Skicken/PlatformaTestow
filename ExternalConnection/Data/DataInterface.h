#pragma once
#include "TestData/AttendanceList.h"
#include "TestData/Groups.h"
#include "TestData/Homework.h"
#include "users/user.h"
#include "TestData/Test.h"
#include "TestData/TestCommit.h"
#include "users/teacher.h"
#include "users/Admin.h"

class Homework;

namespace ExternalData
{
	
	class DataInterface
	{
		public:
		virtual ~DataInterface() = default;

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

			virtual void commitTestResult(TestCommit& result,std::string STUDENT_ID)=0;
			virtual std::vector<TestCommit> getTestResults(std::string STUDENT_ID) = 0;
			virtual void deleteTestResult(TestCommit& result) = 0;

			virtual void addGroup(Group& group) = 0;
			virtual std::vector<Group> getAllGroups() = 0;
			virtual void deleteGroup(Group& group) = 0;

			virtual void addAttendanceList(AttendanceList& list) = 0;
			virtual void deleteAttendanceList(AttendanceList& list) = 0;
			virtual AttendanceList getAttendanceList(Group& group, std::string& Date) = 0;

			virtual void addHomework(Group& group, Homework& homework) = 0;
			virtual std::vector<Homework> getAllHomeworks() = 0;
			virtual void commitHomework(std::string StudentID, HomeworkCommit& homework) = 0;

			virtual std::vector<HomeworkCommit> getCommitedHomeworks(std::string STUDENT_ID) = 0;
			virtual std::vector<HomeworkCommit> getCommitedHomeworks(Homework homework) = 0;

			virtual void deleteHomework(Homework& homework) = 0;

	};
}
