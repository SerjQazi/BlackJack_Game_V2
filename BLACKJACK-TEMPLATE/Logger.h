#pragma once

#include <string>
#include <sstream>

class Logger 
{
public:
    virtual ~Logger() = default;

    template<typename... Args>
    void logInfo(Args... args) 
    {
        log("INFO", args...);
    }

    template<typename... Args>
    void logWarning(Args... args) 
    {
        log("WARNING", args...);
    }

    template<typename... Args>
    void logError(Args... args) 
    {
        log("ERROR", args...);
    }

protected:
    virtual void log(const std::string& level, const std::string& message) = 0;

private:
    template<typename T>
    void formatMessage(std::stringstream& ss, T value) 
    {
        ss << value;
    }

    template<typename T, typename... Args>
    void formatMessage(std::stringstream& ss, T value, Args... args) 
    {
        ss << value;
        formatMessage(ss, args...);
    }

    template<typename... Args>
    void log(const std::string& level, Args... args) 
    {
        std::stringstream ss;
        formatMessage(ss, args...);
        log(level, ss.str());
    }
};