#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Platform
{
	class Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
	public:
		static void INIT();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }

	};
}
#ifndef DIST
	#define ERROR(...)   Platform::Logger::GetCoreLogger()->warn(__VA_ARGS__);
	#define INFO(...)    Platform::Logger::GetCoreLogger()->info(__VA_ARGS__);
	#define TRACE(...)   Platform::Logger::GetCoreLogger()->trace(__VA_ARGS__);
	#define WARN(...)    Platform::Logger::GetCoreLogger()->warn(__VA_ARGS__);
	#define FATAL(...)   Platform::Logger::GetCoreLogger()->critical(__VA_ARGS__);
#else
	#define ERROR(...)
	#define INFO(...)
	#define TRACE(...)
	#define WARN(...)
	#define FATAL(...)
#endif

