#pragma once
namespace ExternalData
{
	enum class ExceptionType{CANNOT_CONNECT,ENTRY_EXISTS,CANNOT_FIND,INVALID_QUERY};
	class DatabaseException final :std::exception
	{
		public:
		DatabaseException(ExceptionType type, const std::string& message);
		~DatabaseException() noexcept override;
		char const* what() const override;
		ExceptionType getType() const;

		private:
		ExceptionType type;
		std::string message;

	};
}

