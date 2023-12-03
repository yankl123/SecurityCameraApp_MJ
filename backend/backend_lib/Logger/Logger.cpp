#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::logger;

bool Logger::loggingEnabled = true; // Enabled by default

void Logger::EnableLogging() {
    loggingEnabled = true;
}

void Logger::DisableLogging() {
    loggingEnabled = false;
}

bool Logger::IsLoggingEnabled() {
    return loggingEnabled;
}

// Other methods remain unchanged

void Logger::Init() {
    spdlog::set_level(spdlog::level::info);

    spdlog::set_pattern("[%H:%M:%S] [%l] %v");

    // Create a file sink
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("my_log_file.txt", true);

    // Create the logger with both console and file sinks
    logger = std::make_shared<spdlog::logger>("my_logger", spdlog::sinks_init_list{fileSink});

    // Set the logger to be the default for the whole application
    spdlog::set_default_logger(logger);
}

std::shared_ptr<spdlog::logger>& Logger::GetLogger() {
    return logger;
}
