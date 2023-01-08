#include "ecpch.h"
#include "MailSender.h"

EmailWrapper::MailSender::MailSender()
{
}

void EmailWrapper::MailSender::sendToGroup(Sender& sender, SimplifiedMessage smplMsg, Group& group)
{
	message msg;
	prepareMessage(msg, sender, smplMsg);
	mailio::mail_group mgroup;
	for(auto user:group.getUsers())
	{
		std::string name_surnameRecipent = user.getName() + " " + user.getSurname();
		mgroup.add(mail_address(name_surnameRecipent, user.getEmail()));
	}
	msg.add_recipient(mgroup);

	mailio::smtps connection(smtpServer, smtpPort);
	connection.authenticate(sender.getEmailLogin(), sender.getEmailPassword(), smtps::auth_method_t::LOGIN);
	connection.submit(msg);
}

void EmailWrapper::MailSender::sendToUser(Sender& sender, SimplifiedMessage smplMsg, User& user)
{
	message msg;
	prepareMessage(msg, sender, smplMsg);

	std::string name_surnameRecipent = user.getName() + " " + user.getSurname();
	msg.add_recipient(mail_address(name_surnameRecipent, user.getEmail()));

	/*mailio::smtps connection(smtpServer, smtpPort);
	connection.authenticate(sender.getEmailLogin(),sender.getEmailPassword(), smtps::auth_method_t::LOGIN);*/

	mailio::smtp connection(smtpServer, smtpPort);
	connection.authenticate(sender.getEmailLogin(), sender.getEmailPassword(), mailio::smtp::auth_method_t::NONE);
	connection.submit(msg);

}

void EmailWrapper::MailSender::prepareMessage(message& msg, Sender& sender, SimplifiedMessage& smplMsg)
{
	std::string name_surname = sender.getUser().getName() + " " + sender.getUser().getSurname();
	msg.from(mail_address(name_surname, sender.getUser().getEmail()));

	msg.subject(smplMsg.getTitle());
	msg.content(smplMsg.getMessage());
}
