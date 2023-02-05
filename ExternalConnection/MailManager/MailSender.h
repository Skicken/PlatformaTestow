#pragma once
#include "TestData/Groups.h"
#include "SimplifiedMessage.h"
#include "users/Sender.h"

namespace EmailWrapper
{
	using mailio::message;
	using mailio::mail_address;
	using mailio::smtps;
	using mailio::smtp_error;
	using mailio::dialog_error;

	class MailSender
	{
		public:
		MailSender() = default;
		void sendToGroup(Sender& sender, SimplifiedMessage smplMsg, Group& group);
		void sendToUser(Sender& sender, SimplifiedMessage smplMsg, User& user);
		private:
		const std::string smtpServer = "smtp.freesmtpservers.com";
		const uint16_t smtpPort = 25;
		void prepareMessage(message& msg,Sender& sender,SimplifiedMessage &smplMsg);

	};
}
