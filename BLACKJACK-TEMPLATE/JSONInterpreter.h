#pragma once

#include "rapidjson/document.h"

#include "Configuration.h"
#include "GameConfiguration.h"
#include "SpriteConfiguration.h"

class JSONInterpreter
{
public:
    virtual void interpret(const std::string& jsonString, Configuration* config);

private:
    void parseGameSettings(const rapidjson::Value& document, GameConfiguration* config);
    void parseSpriteSettings(const rapidjson::Value& document, SpriteConfiguration* config);
};