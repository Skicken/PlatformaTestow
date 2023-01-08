#include "pch.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//Units tests should be run only in release mode.
namespace UnitTests
{
	using namespace EmailWrapper;
	using namespace ExternalData;
	TEST_CLASS(EMAIL_TESTS)
	{
		TEST_METHOD(SEND_TEST_EMAIL)
		{
			DataInterface* data = new MySQL();
			MailSender mailSender;
			User* user = data->getUser("admin", "admin");
			SimplifiedMessage msg("hello world!", "hello world!");
			Sender sender(*user, "test123abe@gmail.com", "Test123qwe!");


			std::string message;
			try
			{
				mailSender.sendToUser(sender, msg, *user);
			}
			catch (smtp_error& e)
			{
				message = std::string(e.what());
			}
			catch (dialog_error& e)
			{
				message = std::string(e.what());
			}
			if(!message.empty())
			{
				Logger::WriteMessage(message.c_str());
			}

		}


	};

}
