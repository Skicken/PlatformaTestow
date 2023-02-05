#pragma once
namespace ExternalData
{
	class UserFactory;
	class MySQL;
}

enum class UserType {  STUDENT = 0 , TEACHER = 1,ADMIN = 2};
class User
{
	public:
	User(const std::string& name, const std::string& surname, const std::string& email, UserType type);
	User(const User& other);
		User(User&& other) noexcept;
		User& operator=(const User& other);
		User& operator=(User&& other) noexcept;


		void setType(UserType type);
		void setName(const std::string& name);
		void setSurname(const std::string& surname);
		bool setEmail(const std::string& email);

		User() = default;
		~User() = default;
		
		std::string	getID() const;
		std::string getName() const;
		std::string getSurname() const;
		std::string getEmail() const;
		UserType getType() const;

	private:
		std::string name;
		std::string surname;
		std::string email;
		UserType type;
		std::string ID;
		User(const std::string& name, const std::string& surname, const std::string& email, UserType type,
			const std::string& id);
		friend class ExternalData::MySQL;
		friend class ExternalData::UserFactory;
};

