#include "knight.h"

#include "druid.h"
#include "elf.h"

Knight::Knight(int x, int y, std::string name) : NPC(KnightType, x, y, name) {}
Knight::Knight(std::istream &is) : NPC(KnightType, is) {}

void Knight::print() { std::cout << *this; }

bool Knight::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::static_pointer_cast<Knight>(shared_from_this()));
}

bool Knight::fight(std::shared_ptr<Knight> other) {
    fight_notify(other, false);
    return false;
}

bool Knight::fight(std::shared_ptr<Druid> other) {
    fight_notify(other, false);
    return false;
}

bool Knight::fight(std::shared_ptr<Elf> other) {
    fight_notify(other, true);
    return true;
}

void Knight::save(std::ostream &os) {
    os << KnightType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Knight &knight) {
    os << "Knight: " << *static_cast<NPC *>(&knight) << std::endl;
    return os;
}
