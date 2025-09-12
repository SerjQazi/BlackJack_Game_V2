#pragma once

#include "Logger.h"

class FileLogger : public Logger 
{
public:
    FileLogger(const std::string& filename);

protected:
    void log(const std::string& level, const std::string& message);

private:
    std::ofstream logFile;
};
