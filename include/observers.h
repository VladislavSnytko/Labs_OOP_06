#pragma once
#include <fstream>

#include "npc.h"


class TextObserver : public IFightObserver {
   private:
    TextObserver(){};

   public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance,
                                               [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker,
                  const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

class FileObserver : public IFightObserver {
   private:
    FileObserver(){};

   public:
    static std::shared_ptr<IFightObserver> get() {
        static FileObserver instance;
        return std::shared_ptr<IFightObserver>(&instance,
                                               [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker,
                  const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::ofstream fs("log.txt", std::ios::app);
            fs << std::endl << "Murder --------" << std::endl;
            fs << attacker->name << " killed " << defender->name << std::endl;
            fs.close();
        }
    }
};
