#include "pch.h"
#include "LoggerManager.h"

LoggerManager::LoggerManager() : logger(nullptr)
{

}

LoggerManager::~LoggerManager()
{
    delete logger;
}

LoggerManager* LoggerManager::getInstance()
{
    if (instance == nullptr)
        instance = new LoggerManager();
    return instance;
}

void LoggerManager::removeInstance()
{
    if (instance)
        delete instance;
}

void LoggerManager::setLogger(Logger* logger)
{
    this->logger = logger;
}

Logger* LoggerManager::getLogger()
{
    return logger;
}

LoggerManager* LoggerManager::instance = nullptr;