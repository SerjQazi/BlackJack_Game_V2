#include "pch.h"
#include "JSONInterpreter.h"

#include "rapidjson/document.h"

void JSONInterpreter::interpret(const std::string& jsonString, Configuration* config)
{
    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (document.HasParseError())
    {
        LOG_ERROR("Cannot parse JSON...");
        return;
    }

    if (document.HasMember("game"))
    {
        const auto& settings = document["game"];

        if (settings.HasMember("settings"))
        {
            parseGameSettings(settings["settings"], dynamic_cast<GameConfiguration*>(config));
        }
    }

    if (document.HasMember("textures"))
    {
        const auto& textureArray = document["textures"];
        for (rapidjson::SizeType i = 0; i < textureArray.Size(); ++i)
        {
            const auto& frameObject = textureArray[i];
            parseSpriteSettings(frameObject, dynamic_cast<SpriteConfiguration*>(config));
        }
    }
}

void JSONInterpreter::parseGameSettings(const rapidjson::Value& document, GameConfiguration* config)
{
    if (document.HasMember("title") && document["title"].IsString())
    {
        config->windowTitle = document["title"].GetString();
    }

    if (document.HasMember("gameloop") && document["gameloop"].IsString())
    {
        config->gameloop = document["gameloop"].GetString();
    }

    if (document.HasMember("renderer") && document["renderer"].IsString())
    {
        config->renderer = document["renderer"].GetString();
    }

    if (document.HasMember("fullscreen") && document["fullscreen"].IsBool())
    {
        config->fullscreen = document["fullscreen"].GetBool();
    }

    if (document.HasMember("x") && document["x"].IsFloat())
    {
        config->x = document["x"].GetFloat();
    }

    if (document.HasMember("y") && document["y"].IsFloat())
    {
        config->y = document["y"].GetFloat();
    }

    if (document.HasMember("zoom") && document["zoom"].IsFloat())
    {
        config->zoom = document["zoom"].GetFloat();
    }

    if (document.HasMember("physics"))
    {
        config->physics = true;

        if (document["physics"].HasMember("gravity"))
        {
            if (document["physics"]["gravity"].HasMember("x") && document["physics"]["gravity"]["x"].IsFloat())
            {
                config->gravity.x = document["physics"]["gravity"]["x"].GetFloat();
            }
            else
                config->gravity.x = 0.0f;

            if (document["physics"]["gravity"].HasMember("y") && document["physics"]["gravity"]["y"].IsFloat())
            {
                config->gravity.y = document["physics"]["gravity"]["y"].GetFloat();
            }
            else
                config->gravity.y = 0.0f;
        }

        if (document["physics"].HasMember("iterations"))
        {
            if (document["physics"]["iterations"].HasMember("velocity") && document["physics"]["iterations"]["velocity"].IsInt())
            {
                config->velocityIterations = document["physics"]["iterations"]["velocity"].GetInt();
            }
            else
                config->velocityIterations = 6;

            if (document["physics"]["iterations"].HasMember("position") && document["physics"]["iterations"]["position"].IsInt())
            {
                config->positionIterations = document["physics"]["iterations"]["position"].GetInt();
            }
            else
                config->positionIterations = 2;
        }

        if (document["physics"].HasMember("debug") && document["physics"]["debug"].IsBool())
        {
            config->debug = document["physics"]["debug"].GetBool();
        }
        else
        {
            config->debug = false;
        }

        if (document["physics"].HasMember("scale") && document["physics"]["scale"].IsFloat())
        {
            config->scale = document["physics"]["scale"].GetFloat();
        }
        else
        {
            config->scale = 1.0f;
        }
    }
    else
    {
        config->physics = false;
    }

    if (document.HasMember("resolution"))
    {
        if (document["resolution"].HasMember("width") && document["resolution"]["width"].IsInt())
        {
            config->SCREEN_WIDTH = document["resolution"]["width"].GetInt();
        }

        if (document["resolution"].HasMember("height") && document["resolution"]["height"].IsInt())
        {
            config->SCREEN_HEIGHT = document["resolution"]["height"].GetInt();
        }
    }

    if (document.HasMember("world"))
    {
        if (document["world"].HasMember("width") && document["world"]["width"].IsInt())
        {
            config->worldWidth = document["resolution"]["width"].GetInt();
        }

        if (document["world"].HasMember("height") && document["world"]["height"].IsInt())
        {
            config->worldHeight = document["world"]["height"].GetInt();
        }
    }
}

void JSONInterpreter::parseSpriteSettings(const rapidjson::Value& document, SpriteConfiguration* config)
{
    if (document.HasMember("image") && document["image"].IsString())
    {
        config->filename = document["image"].GetString();
    }

    if (document.HasMember("size") && document["size"].IsObject())
    {
        const auto& size = document["size"];
        if (size.HasMember("w") && size["w"].IsInt())
        {
            config->spriteSheetWidth = size["w"].GetInt();
        }
        if (size.HasMember("h") && size["h"].IsInt())
        {
            config->spriteSheetHeight = size["h"].GetInt();
        }
    }

    if (document.HasMember("frames") && document["frames"].IsArray())
    {
        const auto& framesArray = document["frames"];
        for (rapidjson::SizeType i = 0; i < framesArray.Size(); ++i)
        {
            const auto& frameObject = framesArray[i];
            std::string frameName;

            if (frameObject.HasMember("filename") && frameObject["filename"].IsString())
            {
                config->id = frameObject["filename"].GetString();
                if (config->id.find('/') != std::string::npos)
                {
                    std::stringstream ss(config->id);
                    std::getline(ss, config->id, '/');
                    std::getline(ss, frameName);
                }
                else
                {
                    frameName = config->id;
                }
            }

            if (frameObject.HasMember("frame") && frameObject["frame"].IsObject())
            {
                Frame frame;
                const auto& frameDetails = frameObject["frame"];

                if (frameName != "")
                    frame.id = frameName;

                if (frameDetails.HasMember("x") && frameDetails["x"].IsInt())
                {
                    frame.source.x = frameDetails["x"].GetInt();
                }
                if (frameDetails.HasMember("y") && frameDetails["y"].IsInt())
                {
                    frame.source.y = frameDetails["y"].GetInt();
                }
                if (frameDetails.HasMember("w") && frameDetails["w"].IsInt())
                {
                    frame.source.w = frameDetails["w"].GetInt();
                }
                if (frameDetails.HasMember("h") && frameDetails["h"].IsInt())
                {
                    frame.source.h = frameDetails["h"].GetInt();
                }

                if (frameName != "")
                    config->frames.insert({ config->id, frame });
            }
        }

        for (auto& item : config->frames)
        {
            config->animations[item.first].addFrame(item.second);
        }

        if (!config->frames.empty())
        {
            config->frameWidth = config->frames.begin()->second.source.w;
            config->frameHeight = config->frames.begin()->second.source.h;
        }

        if (config->frameWidth > 0 && config->frameHeight > 0)
        {
            config->rows = config->spriteSheetWidth / config->frameWidth;
            config->cols = config->spriteSheetHeight / config->frameHeight;
        }
    }
}