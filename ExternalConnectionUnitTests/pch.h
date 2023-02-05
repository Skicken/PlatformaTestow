
#ifndef PCH_H
#define PCH_H
#include <pch.h>
#include <ExternalConnection.h>
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ExternalData;
using namespace EmailWrapper;

inline void failMessage(const std::string& message)
{
	if (!message.empty())
	{
		Logger::WriteMessage(message.c_str());
		Assert::Fail();
	}
}
#endif 
