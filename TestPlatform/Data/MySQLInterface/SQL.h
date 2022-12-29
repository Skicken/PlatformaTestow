#pragma once
#include "../DataInterface.h"
#include "UserFactory.h"
namespace ExternalData
{
	using connection_ptr = std::shared_ptr<sql::Connection>;
	using statement_ptr = std::unique_ptr<sql::PreparedStatement>;
	using result_ptr = std::unique_ptr<sql::ResultSet>;

	class MySQL : public DataInterface
	{

		private:
			const std::string serverIP = "localhost";
			const std::string databaseName = "data";
			sql::Driver* driver;
			connection_ptr getConnection();
		public:
			MySQL();
			~MySQL();

			virtual std::vector<Test> getAllTests() override;
			virtual std::vector<Test> getTeacherTests(std::string OWNER_ID) override;
			virtual void modifyTest(Test& test) override;
			virtual void deleteTest(Test& test) override;
			virtual void addTest(Test& test, std::string OWNER_ID)  override;
			virtual void addUser(User& user, std::string login, std::string password) override;
			virtual void deleteUser(User& user) override;
			virtual void modifyUser(User& user, std::string login, std::string password) override;
			virtual std::vector<Test> getStudentAvailableTest(std::string STUDENT_ID) override;
			virtual void commitTestResult() override;
			virtual void getResults(User& user) override;
			virtual User* getUser(std::string login, std::string password) override;
			virtual void modifyUser(User& user) override;
	};
}