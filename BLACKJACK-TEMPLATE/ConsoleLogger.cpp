#include "pch.h"
#include "ConsoleLogger.h"

void ConsoleLogger::log(const std::string& level, const std::string& message)
{
    std::cout << level << ": " << message << std::endl;
}