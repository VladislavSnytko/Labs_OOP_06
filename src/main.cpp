#include <algorithm>
#include <ctime>

#include "druid.h"
#include "elf.h"
#include "factory.h"
#include "knight.h"
#include "npc.h"

// save array to file
void save(const set_t &array, const std::string &filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array) n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) result.insert(factory(is));
        is.close();
    } else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array) n->print();
    return os;
}

set_t fight(const set_t &array, size_t distance) {
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) &&
                (attacker->is_close(defender, distance))) {
                bool success = defender->accept(attacker);
                if (success) dead_list.insert(defender);
            }

    return dead_list;
}

int main() {
    set_t array;
    std::string filename = "npc.txt";

    std::srand(std::time(nullptr));

    while (true) {
        std::cout << "1. Add NPC" << std::endl;
        std::cout << "2. Save to file" << std::endl;
        std::cout << "3. Load from file" << std::endl;
        std::cout << "4. Print list" << std::endl;
        std::cout << "5. Battle mode" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "> ";

        int choice;
        if (!(std::cin >> choice)) {
            break;
        }

        if (choice == 1) {
            int type_int;
            int x, y;
            std::string name;
            std::cout << "Type (1-Knight, 2-Druid, 3-Elf): ";
            std::cin >> type_int;
            std::cout << "X (0-500): ";
            std::cin >> x;
            std::cout << "Y (0-500): ";
            std::cin >> y;
            std::cout << "Name: ";
            std::cin >> name;

            if (x < 0 || x > 500 || y < 0 || y > 500) {
                std::cout << "Invalid coordinates!" << std::endl;
                continue;
            }

            bool name_exists = false;
            for (const auto &npc : array) {
                if (npc->name == name) {
                    name_exists = true;
                    break;
                }
            }

            if (name_exists) {
                std::cout << "Error: Name already exists!" << std::endl;
                continue;
            }

            array.insert(factory(NpcType(type_int), x, y, name));
        } else if (choice == 2) {
            std::cout << "Filename: ";
            std::cin >> filename;
            save(array, filename);
            std::cout << "Saved to " << filename << std::endl;
        } else if (choice == 3) {
            std::cout << "Filename: ";
            std::cin >> filename;
            array = load(filename);
            std::cout << "Loaded from " << filename << std::endl;
        } else if (choice == 4) {
            std::cout << array << std::endl;
        } else if (choice == 5) {
            int distance;
            std::cout << "Enter fight distance: ";
            std::cin >> distance;

            set_t dead_list = fight(array, distance);
            for (auto &d : dead_list) array.erase(d);

            std::cout << "Killed: " << dead_list.size() << std::endl;
        } else if (choice == 6) {
            break;
        }
    }

    return 0;
}
