#include "ecpch.h"
#include "Utilities.h"
namespace ExternalData
{
	std::string Utilities::generateID(connection_shared connection)
	{
		const std::string query = "Select " + ID_GEN;
		statement_unique statement(connection->prepareStatement(query));
		result_unique result(statement->executeQuery());
		if (result->next())
		{
			return result->getString(1);
		}
		return "";
	}
}
