#pragma once

#include "Logger.h"

class ConsoleLogger : public Logger 
{
protected:
    void log(const std::string& level, const std::string& message);
};