#include "ptpch.h"
#include "Logger.h"
#pragma warning(push, 0)
std::shared_ptr<spdlog::logger> Logger::coreLogger;
void Logger::INIT()
{
	spdlog::set_pattern("%^[%T][%n]: %v%$");
	coreLogger = spdlog::stdout_color_mt("TestPlatform");
	coreLogger->set_level(spdlog::level::trace);
	coreLogger->info("Logger working!");
}
