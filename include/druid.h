#pragma once
#include "npc.h"

struct Druid : public NPC
{
    Druid(int x, int y, std::string name);
    Druid(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<Knight> other) override;
    bool fight(std::shared_ptr<Druid> other) override;
    bool fight(std::shared_ptr<Elf> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Druid &druid);
};
