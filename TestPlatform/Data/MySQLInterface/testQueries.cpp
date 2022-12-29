#include "ptpch.h"
#include "SQL.h"
#include "TestFactory.h"

namespace ExternalData
{


	void MySQL::modifyTest(Test& test)
	{

	}
	void MySQL::deleteTest(Test& test)
	{

	}
	void MySQL::addTest(Test& test, std::string OWNER_ID)
	{
		const std::string query = "INSERT INTO `tests`(`ID`, `OWNER_ID`, `name`, `randomize`, `description`) VALUES (UNHEX(REPLACE(UUID(),?,?,?,?)";
		connection_ptr connection = getConnection();

		statement_ptr testQuery(connection->prepareStatement(query));
		testQuery->setString(1, OWNER_ID);
		testQuery->setString(2, test.getTestName());
		testQuery->setBoolean(3, test.getRandomize());
		testQuery->setString(4, test.getDescription());
		testQuery->execute();

		const auto  factory = std::make_unique<TestFactory>(connection);

	}
	std::vector<Test> MySQL::getAllTests()
	{
		connection_ptr connection = this->getConnection();
		const auto  factory = std::make_unique<TestFactory>(connection);
		return factory->getAllTests();

	}
	std::vector<Test> MySQL::getStudentAvailableTest(std::string STUDENT_ID)
	{
		connection_ptr connection = this->getConnection();
		const auto factory = std::make_unique<TestFactory>(connection);
		return factory->getAssignedTests(STUDENT_ID);

	}
	std::vector<Test> MySQL::getTeacherTests(std::string OWNER_ID)
	{
		connection_ptr connection = this->getConnection();
		const auto factory = std::make_unique<TestFactory>(connection);
		return factory->getOwnerTest(OWNER_ID);
	}
}
