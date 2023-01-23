#pragma once
#include "../DataInterface.h"
#include "DatabaseException.h"
namespace ExternalData
{
	const std::string ID_GEN = "UNHEX(REPLACE(UUID(), '-', ''))";
	using connection_shared = std::shared_ptr<sql::Connection>;
	using statement_unique = std::unique_ptr<sql::PreparedStatement>;
	using result_unique = std::unique_ptr<sql::ResultSet>;
	using result_shared = std::shared_ptr<sql::ResultSet>;
	class MySQL : public DataInterface
	{

		private:
			const std::string serverIP = "localhost";
			const std::string databaseName = "data";
			sql::Driver* driver;
			connection_shared getConnection();
		public:
			MySQL();
			~MySQL() override;
			std::string getUniqueID();
			std::string getCurrentDate() override;
			virtual std::vector<Test> getAllTests() override;
			virtual std::vector<Test> getTeacherTests(std::string OWNER_ID) override;
			virtual void modifyTest(Test& test, std::string OWNER_ID) override;
			virtual void deleteTest(Test& test) override;
			virtual void addTest(Test& test, std::string OWNER_ID)  override;
			virtual void addUser(User& user, std::string login, std::string password) override;
			virtual void deleteUser(User& user) override;
			virtual void modifyUser(User& user, std::string login, std::string password) override;
			virtual std::vector<Test> getStudentAvailableTest(std::string STUDENT_ID) override;
			virtual std::shared_ptr<User> getUser(std::string login, std::string password) override;
			virtual void modifyUser(User& user) override;

			std::vector<User> getAllUsers() override;
			void commitTestResult(TestCommit& result, std::string STUDENT_ID) override;
			virtual std::vector<TestCommit> getTestResults(std::string STUDENT_ID) override;
			void addGroup(Group& group) override;
			std::vector<Group> getAllGroups() override;
			void deleteGroup(Group& group) override;
			void addAttendanceList(AttendanceList& list) override;
			void deleteAttendanceList(AttendanceList& list) override;
			virtual AttendanceList getAttendanceList(Group& group, std::string& Date) override;

			std::vector<User> getGroupUsers(std::string groupID);
			void deleteTestResult(TestCommit& result) override;

			void addHomework(Group& group, Homework& homework) override;
			std::vector<Homework> getAllHomework() override;
			void commitHomework(std::string StudentID, HomeworkCommit& homework) override;
			std::vector<HomeworkCommit> getCommitHomework(std::string STUDENT_ID) override;
			std::vector<HomeworkCommit> getCommitHomework(Homework homework) override;
			void deleteHomework(Homework& homework) override;
			std::vector<Homework> getAllAvailableHomework(std::string USER_ID) override;
			std::vector<AttendanceList> getGroupAttendanceList(Group& group) override;
	};
}