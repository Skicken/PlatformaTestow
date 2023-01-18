#include "ecpch.h"
#include "UserFactory.h"
namespace ExternalData
{

	std::shared_ptr<User> UserFactory::createUserFrom(const std::string& name, const std::string& surname, const std::string& email, const std::string& id, const std::string& type)
	{
		return std::make_shared<User>(User(name, surname, email, StringToEnum(type), id));
	}

	User UserFactory::getUserFromRow(result_shared result)
	{
		User user = *createUserFrom(
			result->getString(1),
			result->getString(2),
			result->getString(3),
			result->getString(4),
			result->getString(5));
		return user;
	}

	User UserFactory::getUserFromID(connection_shared connection, std::string ID)
	{
		std::string query = "select name, surname, email, ID, accountType from users where ID = ?";
		statement_unique statement(connection->prepareStatement(query));
		statement->setString(1, ID);
		const result_shared result(statement->executeQuery());
		if (!result->next()) throw DatabaseException(ExceptionType::CANNOT_FIND, "Cannot find user with specified id");
		return getUserFromRow(result);
	}
}
