#pragma once
#include "npc.h"
#include "knight.h"
#include "druid.h"
#include "elf.h"
#include "observers.h"

std::shared_ptr<NPC> factory(std::istream &is)
{
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type)
    {
        switch (type)
        {
        case KnightType:
            result = std::make_shared<Knight>(is);
            break;
        case DruidType:
            result = std::make_shared<Druid>(is);
            break;
        case ElfType:
            result = std::make_shared<Elf>(is);
            break;
        }
    }
    else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y, std::string name)
{
    std::shared_ptr<NPC> result;
    switch (type)
    {
    case KnightType:
        result = std::make_shared<Knight>(x, y, name);
        break;
    case DruidType:
        result = std::make_shared<Druid>(x, y, name);
        break;
    case ElfType:
        result = std::make_shared<Elf>(x, y, name);
        break;
    default:
        break;
    }
    if (result) {
        result->subscribe(TextObserver::get());
        result->subscribe(FileObserver::get());
    }

    return result;
}
