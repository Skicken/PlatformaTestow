#pragma once
class User
{
	enum class UserType{ADMIN,STUDENT,TEACHER};
	std::string name;
	std::string surname;
	std::string email;
	const std::string uuid;
	UserType type;

public:
	void setType(UserType type);
	void setName(const std::string& name);
	void setSurname(const std::string& surname);
	bool setEmail(const std::string& email);

	virtual ~User() = default;
	User(const std::string& name, const std::string& surname, const std::string& email, const std::string& uuid,
		UserType type);
	virtual void setMainView() = 0;

	std::string	getUUID() const;
	std::string getName() const;
	std::string getSurname() const;
	std::string getEmail() const;
	UserType getType() const;


};

