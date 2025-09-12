#pragma once

#include "JSONInterpreter.h"
#include "Configuration.h"
#include "GameConfiguration.h"
#include "SpriteConfiguration.h"

class ConfigurationManager
{
public:
    ~ConfigurationManager();

    static ConfigurationManager* getInstance();
    static void removeInstance();

    void loadConfiguration(const std::string& filename, Configuration* config);
    void loadConfiguration(const std::string& filename, Configuration* config, JSONInterpreter* customInterpreter);

    Configuration& getGameConfiguration(std::string filename);

private:
    ConfigurationManager();
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    JSONInterpreter interpreter;

    std::unordered_map<std::string, Configuration*> configurations;

    static ConfigurationManager* instance;
};
