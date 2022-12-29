#include "ptpch.h"
#include "SQL.h"
namespace ExternalData
{
	void MySQL::addUser(User& user, std::string login, std::string password)
	{
		const std::string query = "INSERT INTO users VALUES (UNHEX(REPLACE(UUID(), '-', '')), ?, MD5(?), ?,?,?,?)";

		connection_ptr connection = this->getConnection();
		statement_ptr stat(connection->prepareStatement(query));

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
		connection_ptr connection = this->getConnection();
		statement_ptr stat(connection->prepareStatement(query));

		stat->setString(1, user.getUUID());
		stat->execute();

	}
	void MySQL::modifyUser(User& user, std::string login, std::string password)
	{
		const std::string query = "UPDATE `users` SET login=?,password=MD5(?),name=?,surname=?,accountType=?,email=? WHERE ID = ?";
		connection_ptr connection = this->getConnection();
		statement_ptr stat(connection->prepareStatement(query));
		stat->setString(1, login);
		stat->setString(2, password);
		stat->setString(3, user.getName());
		stat->setString(4, user.getSurname());
		stat->setString(5, UserFactory::EnumToString(user.getType()));
		stat->setString(6, user.getEmail());
		stat->setString(7, user.getUUID());

		stat->execute();

	}
	User* MySQL::getUser(std::string login, std::string password)
	{
		const std::string query = "select name,surname,email,ID,accountType from users where login = ? and password = MD5(?)";
		connection_ptr connection = this->getConnection();
		statement_ptr stat(connection->prepareStatement(query));

		stat->setString(1, login);
		stat->setString(2, password);

		result_ptr result(stat->executeQuery());
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
		connection_ptr connection = this->getConnection();
		statement_ptr stat(connection->prepareStatement(query));
		stat->setString(1, user.getName());
		stat->setString(2, user.getSurname());
		stat->setString(3, UserFactory::EnumToString(user.getType()));
		stat->setString(4, user.getEmail());
		stat->setString(5, user.getUUID());
		stat->execute();

	}
}