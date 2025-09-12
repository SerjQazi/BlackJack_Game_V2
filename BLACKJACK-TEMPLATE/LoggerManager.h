#pragma once

#include "Logger.h"

#ifdef _DEBUG
#define LOG_INFO(...) LoggerManager::getInstance()->getLogger()->logInfo(__VA_ARGS__)
#define LOG_WARNING(...) LoggerManager::getInstance()->getLogger()->logWarning(__VA_ARGS__)
#define LOG_ERROR(...) LoggerManager::getInstance()->getLogger()->logError(__VA_ARGS__)
#else
#define LOG_INFO(...)
#define LOG_WARNING(...)
#define LOG_ERROR(...)
#endif

class LoggerManager
{
public:
    static LoggerManager* getInstance();
    static void removeInstance();

    void setLogger(Logger* logger);

    Logger* getLogger();

private:
    LoggerManager();
    ~LoggerManager();

    Logger* logger;

    static LoggerManager* instance;
};
