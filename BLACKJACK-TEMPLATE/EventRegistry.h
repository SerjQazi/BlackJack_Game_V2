#pragma once

#include "Key.h"

class EventRegistry
{
public:
    static EventRegistry* getInstance();
    static void removeInstance();

    void registerEvent(const std::string& str);
    void registerComboEvent(std::vector<Key::Code> combo);
    std::string findEvent(int code);
    
    int generateCode(const std::string& str);

    std::vector<std::vector<Key::Code>> getCombos() const;

private:
    EventRegistry();
    ~EventRegistry();

    std::vector<std::vector<Key::Code>> combos;
    std::unordered_map<int, std::string> codeMap;

    static const unsigned long HASH_SEED;
    static EventRegistry* instance;
};