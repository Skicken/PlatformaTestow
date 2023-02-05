#include "ecpch.h"
#include "ExternalDatabase/MySQLInterface/Helpers/UserFactory.h"
#include "ExternalDatabase/MySQLInterface/SQL.h"
#include "ExternalDatabase/MySQLInterface/Helpers/UserValidator.h"

namespace ExternalData
{
	void MySQL::addUser(User& user, std::string login, std::string password)
	{
		std::string error = UserValidator::validateUser(user, login, password);
		if (!error.empty()) throw DatabaseException(ExceptionType::INVALID_QUERY, error);

		const std::string query = "INSERT INTO users VALUES ("+ID_GEN+", ?, MD5(?), ?,?,?,?)";
		connection_shared connection = this->getConnection();
		statement_unique stat(connection->prepareStatement(query));

		stat->setString(1, login);
		stat->setString(2, password);
		stat->setString(3, user.getName());
		stat->setString(4, user.getSurname());
		stat->setString(5, EnumToString(user.getType()));
		stat->setString(6, user.getEmail());
		try
		{
			stat->execute();
		}
		catch (sql::SQLException& exception)
		{
			throw DatabaseException(ExceptionType::ENTRY_EXISTS, "User with such login exists");
		}
		

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
		std::string error = UserValidator::validateUser(user, login, password);
		if (!error.empty()) throw DatabaseException(ExceptionType::INVALID_QUERY, error);

		const std::string query = "UPDATE `users` SET login=?,password=MD5(?),name=?,surname=?,accountType=?,email=? WHERE ID = ?";
		connection_shared connection = this->getConnection();
		statement_unique stat(connection->prepareStatement(query));
		stat->setString(1, login);
		stat->setString(2, password);
		stat->setString(3, user.getName());
		stat->setString(4, user.getSurname());
		stat->setString(5, EnumToString(user.getType()));
		stat->setString(6, user.getEmail());
		stat->setString(7, user.getID());
		stat->execute();

	}
	std::shared_ptr<User> MySQL::getUser(std::string login, std::string password)
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
		stat->setString(3, EnumToString(user.getType()));
		stat->setString(4, user.getEmail());
		stat->setString(5, user.getID());

		stat->execute();

	}
	std::vector<User> MySQL::getAllUsers()
	{
		connection_shared connection = getConnection();
		std::string query = "select name, surname, email, ID, accountType from users";
		statement_unique statement(connection->prepareStatement(query));
		result_shared result(statement->executeQuery());

		std::vector<User> users;
		const std::unique_ptr<UserFactory> userFactory;
		while(result->next())
		{
			users.push_back(userFactory->getUserFromRow(result));
		}
		return users;
	}

}
