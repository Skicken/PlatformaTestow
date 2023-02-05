#pragma once
#include "Answer.h"

namespace ExternalData
{
	class TestGetter;
	class MySQL;
}

class Question
{
	public:
	Question(const Question& other);
	Question(Question&& other) noexcept;
	Question& operator=(const Question& other);
	Question& operator=(Question&& other) noexcept;

		Question(const std::string& question);
		Question(const std::string& question, const std::vector<Answer> answers, const Answer& correct_answer);

		std::string getQuestionID() const;
		std::string getQuestionName() const;
		void setQuestion(const std::string& question);
		std::vector<Answer>& getAnswers();
		void setAnswers(const std::vector<Answer> answers);
		Answer getCorrectAnswer() const;
		void setCorrectAnswer(const Answer& correct_answer);
	private:
		Question(const std::string& question_id, const std::string& question, const std::vector<Answer> answers,
			const Answer& correct_answer);
		std::string QuestionID;
		std::string question;
		std::vector<Answer> answers;
		Answer correctAnswer;
		friend class ExternalData::MySQL;
		friend class ExternalData::TestGetter;

	
};

