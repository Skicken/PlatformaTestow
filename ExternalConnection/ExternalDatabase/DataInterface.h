#pragma once
#include "TestData/AttendanceList.h"
#include "TestData/Groups.h"
#include "TestData/Homework.h"
#include "users/user.h"
#include "TestData/Test.h"
#include "TestData/TestCommit.h"



namespace ExternalData
{
	extern UserType StringToEnum(std::string value);
	extern std::string EnumToString(UserType type);
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
			virtual std::shared_ptr<User> getUser(std::string login, std::string password) = 0;
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
			virtual std::vector<AttendanceList> getGroupAttendanceList(Group& group) = 0;
			virtual void addHomework(Group& group, Homework& homework) = 0;
			virtual std::vector<Homework> getAllHomework() = 0;
			virtual void commitHomework(std::string StudentID, HomeworkCommit& homework) = 0;

			virtual std::vector<HomeworkCommit> getCommitHomework(std::string STUDENT_ID) = 0;
			virtual std::vector<HomeworkCommit> getCommitHomework(Homework homework) = 0;

			virtual void deleteHomework(Homework& homework) = 0;
			virtual std::vector<Homework> getAllAvailableHomework(std::string USER_ID) = 0;
			virtual std::string getCurrentDate() = 0;

	};
}
