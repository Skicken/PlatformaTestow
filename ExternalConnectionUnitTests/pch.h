
#ifndef PCH_H
#define PCH_H
#include <pch.h>
#include <ExternalConnection.h>
#include "CppUnitTest.h"
inline void failMessage(std::string& message)
{
	if (!message.empty())
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(message.c_str());
		Microsoft::VisualStudio::CppUnitTestFramework::Assert::Fail();
	}
}
#endif 
