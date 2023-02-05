#include "pch.h"


//Units tests should be run only in release mode.
namespace UnitTests
{

	TEST_CLASS(CONNECTION)
	{
		TEST_METHOD(AddSameUser)
		{
			std::string message;
			DataInterface* data = new MySQL();

			//adding user
			std::shared_ptr<User> user = std::shared_ptr<User>{ new User("name", "surname", "name@mail.pl",UserType::TEACHER) };
			data->addUser(*user, "root", "root");
			try
			{
				data->addUser(*user, "root", "root");
			}
			catch(DatabaseException& exception)
			{
				Assert::IsTrue(exception.getType() == ExceptionType::ENTRY_EXISTS);
				Logger::WriteMessage("entry already exists");
			}
			data->deleteUser(*data->getUser("root", "root"));
		}

	};

}
