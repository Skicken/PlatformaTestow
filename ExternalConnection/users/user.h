#pragma once
enum class UserType { ADMIN, STUDENT, TEACHER };
class User
{
public:
	User(const User& other);

	User(User&& other) noexcept;

	User& operator=(const User& other);

	User& operator=(User&& other) noexcept;

protected:
	std::string name;
	std::string surname;
	std::string email;
	std::string ID;
	UserType type;

	public:
	void setType(UserType type);
	void setName(const std::string& name);
	void setSurname(const std::string& surname);
	bool setEmail(const std::string& email);

	virtual ~User();
	User(const std::string& name, const std::string& surname, const std::string& email,	const std::string& uuid);
	User(const std::string& name, const std::string& surname, const std::string& email);

	std::string	getID() const;
	std::string getName() const;
	std::string getSurname() const;
	std::string getEmail() const;
	UserType getType() const;


};

