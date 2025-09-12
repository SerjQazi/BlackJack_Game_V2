#include "pch.h"
#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager()
{
    LOG_INFO("Initializing configuration manager...");
}

ConfigurationManager::~ConfigurationManager()
{
    for (auto& item : configurations)
    {
        if (item.second)
        {
            delete item.second;
            item.second = nullptr;
        }
    }
    configurations.clear();
}

ConfigurationManager* ConfigurationManager::getInstance()
{
    if(instance == nullptr)
        instance = new ConfigurationManager();
    return instance;
}

void ConfigurationManager::removeInstance()
{
    if (instance)
        delete instance;
}

void ConfigurationManager::loadConfiguration(const std::string& filename, Configuration* config)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        LOG_ERROR("Cannot open configuration ", filename, "...");
        return;
    }

    LOG_INFO("Reading ", filename, "...");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonString = buffer.str();

    configurations[filename] = config;

    interpreter.interpret(jsonString, config);
}

void ConfigurationManager::loadConfiguration(const std::string& filename, Configuration* config, JSONInterpreter* customInterpreter)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        LOG_ERROR("Cannot open configuration ", filename, "...");
        return;
    }

    LOG_INFO("Reading ", filename, "...");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonString = buffer.str();

    configurations[filename] = config;

    customInterpreter->interpret(jsonString, config);
}

Configuration& ConfigurationManager::getGameConfiguration(std::string filename)
{
    return *configurations[filename];
}

ConfigurationManager* ConfigurationManager::instance = nullptr;