#define _CRT_SECURE_NO_WARNINGS
#include "logger.h"

#include <iostream>
#include <ctime>
#include <cassert>

#include <SDL.h>

bool Logger::enabled_ = true;
std::ostream *Logger::os_ = &std::cerr;

void Logger::LogHeader(const std::string &log_type) {//输出错误类型
    char buffer[100];
    auto format = "%Y-%m-%d %T";
    auto now = std::time(nullptr);
    if (std::strftime(buffer, 100, format, std::localtime(&now))) {
        *os_ << buffer << ' ';
    }
    *os_ << '[' << log_type << "] ";
}

void Logger::LogError(const std::string &message) {//SDL初始化等方面出错
    if (!enabled_) return;
    auto error_msg = SDL_GetError();
    LogHeader("error");
    *os_ << message;
    if (error_msg && error_msg[0] != '\0') {
        *os_ << ", SDL message: " << error_msg;
    }
    *os_ << std::endl;
}

void Logger::LogInfo(const std::string &message) {//信息处理出错
    if (!enabled_) return;
    LogHeader("info");
    *os_ << message << std::endl;
}

void Logger::LogDebug(const std::string &message) {//debug过程出错
#if DEBUG
    if (!enabled_) return;
    LogHeader("debug");
    *os_ << message << std::endl;
#endif
}
