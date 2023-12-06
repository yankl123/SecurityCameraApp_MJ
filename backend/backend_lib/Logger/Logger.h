#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class Logger {
public:
    static void Init();
    static void EnableLogging(); // Enable logging (default)
    static void DisableLogging(); // Disable logging
    static bool IsLoggingEnabled(); // Check if logging is currently enabled

    static std::shared_ptr<spdlog::logger>& GetLogger();

private:
    static std::shared_ptr<spdlog::logger> logger;
    static bool loggingEnabled;
};


#define LOG_INFO(...)    if(Logger::IsLoggingEnabled()) Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_DEBUG(...)   if(Logger::IsLoggingEnabled()) Logger::GetLogger()->debug(__VA_ARGS__)
#define LOG_ERROR(...)   if(Logger::IsLoggingEnabled()) Logger::GetLogger()->error(__VA_ARGS__)
#define LOG_WARN(...)    if(Logger::IsLoggingEnabled()) Logger::GetLogger()->warn(__VA_ARGS__)
