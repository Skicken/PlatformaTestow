#pragma once
#include "users/user.h"
#include "TestData/Test.h"
class DataInterface
{
	virtual std::vector<Test>& getAllTests() = 0;
	virtual std::vector<Test>& getTeacherTests(int USER_ID) = 0;

};

