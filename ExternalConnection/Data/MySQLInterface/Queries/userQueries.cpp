#include "ecpch.h"
#include "Data/MySQLInterface/SQL.h"
#include "Data/MySQLInterface/Helpers/UserFactory.h"

namespace ExternalData
{
	void MySQL::addUser(User& user, std::string login, std::string password)
	{
		const std::string query = "INSERT INTO users VALUES (UNHEX(REPLACE(UUID(), '-', '')), ?, MD5(?), ?,?,?,?)";

		connection_shared connection = this->getConnection();
		statement_unique stat(connection->prepareStatement(query));

		stat->setString(1, login);
		stat->setString(2, password);
		stat->setString(3, user.getName());
		stat->setString(4, user.getSurname());
		stat->setString(5, UserFactory::EnumToString(user.getType()));
		stat->setString(6, user.getEmail());

		stat->execute();

	}
	void MySQL::deleteUser(User& user)
	{
		const std::string query = "delete from users where ID = CAST(? as Binary)";
		connection_shared connection = this->getConnection();
		statement_unique stat(connection->prepareStatement(query));

		stat->setString(1, user.getID());
		stat->execute();
	}
	void MySQL::modifyUser(User& user, std::string login, std::string password)
	{
		const std::string query = "UPDATE `users` SET login=?,password=MD5(?),name=?,surname=?,accountType=?,email=? WHERE ID = ?";
		connection_shared connection = this->getConnection();
		statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, login);
		stat->setString(2, password);
		stat->setString(3, user.getName());
		stat->setString(4, user.getSurname());
		stat->setString(5, UserFactory::EnumToString(user.getType()));
		stat->setString(6, user.getEmail());
		stat->setString(7, user.getID());

		stat->execute();

	}
	User* MySQL::getUser(std::string login, std::string password)
	{
		const std::string query = "select name,surname,email,ID,accountType from users where login = ? and password = MD5(?)";
		connection_shared connection = this->getConnection();
		statement_unique stat(connection->prepareStatement(query));

		stat->setString(1, login);
		stat->setString(2, password);

		result_unique result(stat->executeQuery());
		std::unique_ptr<UserFactory> factory;
		if (result->next())
		{
			return factory->createUserFrom(
				result->getString(1),
				result->getString(2),
				result->getString(3),
				result->getString(4),
				result->getString(5));
		}
		return nullptr;

	}

	void MySQL::modifyUser(User& user)
	{
		const std::string query = "UPDATE `users` SET name=?,surname=?,accountType=?,email=? WHERE ID = ?";
		connection_shared connection = this->getConnection();
		statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, user.getName());
		stat->setString(2, user.getSurname());
		stat->setString(3, UserFactory::EnumToString(user.getType()));
		stat->setString(4, user.getEmail());
		stat->setString(5, user.getID());
		stat->execute();

	}

	std::vector<User> MySQL::getAllUsers()
	{
		return std::vector<User>();
	}

	void MySQL::addTestResult(TestResult& result, std::string STUDENT_ID)
	{
	}

	std::vector<TestResult> MySQL::getTestResults(std::string STUDENT_ID)
	{
	}

	void MySQL::addGroup(Group& group)
	{
	}

	std::vector<Group> MySQL::getAllGroups()
	{
		return std::vector<Group>();
	}

	void MySQL::deleteGroup(Group& group)
	{
	}
	
}
