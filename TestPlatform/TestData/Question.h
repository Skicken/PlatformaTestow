#pragma once
#include "Answer.h"
class Question
{

private:
		std::string QuestionID;
		std::string question;
		std::vector<Answer> answers;
	public:
		Question(const std::string& question_id, const std::string& question);
		Question(const std::string& question_id, const std::string& question, const std::vector<Answer>& answers);
		std::string getQuestionID() const;
		std::string getQuestionName() const;
		void setQuestion(const std::string& question);
		std::vector<Answer> getAnswers() const;
		void setAnswers(const std::vector<Answer>& answers);

		Question(const Question& other);
		Question(Question&& other) noexcept;
		Question& operator=(const Question& other);
		Question& operator=(Question&& other) noexcept;
};

