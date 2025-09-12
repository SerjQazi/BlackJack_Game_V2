#include "pch.h"
#include "FileLogger.h"

FileLogger::FileLogger(const std::string& filename) : logFile(filename, std::ios::app) 
{ }

void FileLogger::log(const std::string& level, const std::string& message)
{
    logFile << level << ": " << message << std::endl;
}