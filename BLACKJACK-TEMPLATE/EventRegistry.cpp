#include "pch.h"
#include "EventRegistry.h"

EventRegistry::EventRegistry()
{ }

EventRegistry::~EventRegistry()
{ }

EventRegistry* EventRegistry::getInstance()
{
    if (instance == nullptr)
        instance = new EventRegistry();
    return instance;
}

void EventRegistry::removeInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void EventRegistry::registerEvent(const std::string& str)
{
    int code = generateCode(str);
    codeMap[code] = str;
}

void EventRegistry::registerComboEvent(std::vector<Key::Code> combo)
{
    combos.push_back(combo);
}

std::string EventRegistry::findEvent(int code)
{
    auto it = codeMap.find(code);
    if (it != codeMap.end())
    {
        return it->second;
    }
    return "";
}

int EventRegistry::generateCode(const std::string& str)
{
    unsigned long hash = HASH_SEED;
    for (char c : str)
    {
        hash = ((hash << 5) + hash) + c;
    }
    
    return static_cast<int>(hash & 0x7FFFFFFF);
}

std::vector<std::vector<Key::Code>> EventRegistry::getCombos() const
{
    return combos;
}

const unsigned long EventRegistry::HASH_SEED = 5381;
EventRegistry* EventRegistry::instance = nullptr;