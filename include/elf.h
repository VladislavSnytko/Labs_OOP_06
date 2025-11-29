#pragma once
#include "npc.h"

struct Elf : public NPC {
    Elf(int x, int y, std::string name);
    Elf(std::istream &is);

    void print() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<Knight> other) override;
    bool fight(std::shared_ptr<Druid> other) override;
    bool fight(std::shared_ptr<Elf> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Elf &elf);
};
