#include "ptpch.h"
#include "Question.h"

bool Question::isCorrect()
{
	return this->correctAnswerID == this->studentAnswerID;
}
