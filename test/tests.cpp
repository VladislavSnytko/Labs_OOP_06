#include <gtest/gtest.h>
#include "npc.h"
#include "knight.h"
#include "druid.h"
#include "elf.h"
#include "factory.h"

TEST(NPCTest, FightKnightVsElf) {
    auto knight = std::make_shared<Knight>(0, 0, "Arthur");
    auto elf = std::make_shared<Elf>(0, 0, "Legolas");
    
    // Knight attacks Elf
    // Elf->accept(Knight) -> Knight->fight(Elf)
    // Variant: "Рыцарь убивает эльфа" -> True
    EXPECT_TRUE(elf->accept(knight));

    // Elf attacks Knight
    // Knight->accept(Elf) -> Elf->fight(Knight)
    // Variant: "Эльф убивает ... рыцаря" -> True
    EXPECT_TRUE(knight->accept(elf));
}

TEST(NPCTest, FightElfVsDruid) {
    auto elf = std::make_shared<Elf>(0, 0, "Legolas");
    auto druid = std::make_shared<Druid>(0, 0, "Panoramix");

    // Elf attacks Druid
    // Druid->accept(Elf) -> Elf->fight(Druid)
    // Variant: "Эльф убивает друида" -> True
    EXPECT_TRUE(druid->accept(elf));

    // Druid attacks Elf
    // Elf->accept(Druid) -> Druid->fight(Elf)
    // Variant: Druid does not kill Elf -> False
    EXPECT_FALSE(elf->accept(druid));
}

TEST(NPCTest, FightDruidVsDruid) {
    auto druid1 = std::make_shared<Druid>(0, 0, "Panoramix");
    auto druid2 = std::make_shared<Druid>(1, 1, "Getafix");

    // Druid attacks Druid
    // Druid2->accept(Druid1) -> Druid1->fight(Druid2)
    // Variant: "Друид убивает друидов" -> True
    EXPECT_TRUE(druid2->accept(druid1));
}

TEST(NPCTest, FightKnightVsDruid) {
    auto knight = std::make_shared<Knight>(0, 0, "Arthur");
    auto druid = std::make_shared<Druid>(0, 0, "Panoramix");

    // Knight attacks Druid -> False
    EXPECT_FALSE(druid->accept(knight));

    // Druid attacks Knight -> False
    EXPECT_FALSE(knight->accept(druid));
}

TEST(NPCTest, FightKnightVsKnight) {
    auto k1 = std::make_shared<Knight>(0, 0, "K1");
    auto k2 = std::make_shared<Knight>(10, 10, "K2");
    EXPECT_FALSE(k1->accept(k2));
    EXPECT_FALSE(k2->accept(k1));
}

TEST(NPCTest, FightElfVsElf) {
    auto e1 = std::make_shared<Elf>(0, 0, "E1");
    auto e2 = std::make_shared<Elf>(10, 10, "E2");
    EXPECT_FALSE(e1->accept(e2));
    EXPECT_FALSE(e2->accept(e1));
}

TEST(NPCTest, IsClose) {
    auto n1 = std::make_shared<Knight>(0, 0, "N1");
    auto n2 = std::make_shared<Elf>(3, 4, "N2"); // Distance = 5
    
    EXPECT_TRUE(n1->is_close(n2, 5));
    EXPECT_TRUE(n1->is_close(n2, 6));
    EXPECT_FALSE(n1->is_close(n2, 4));
}

TEST(NPCTest, FactoryType) {
    auto n1 = factory(KnightType, 0, 0, "K");
    EXPECT_TRUE(std::dynamic_pointer_cast<Knight>(n1) != nullptr);
    
    auto n2 = factory(DruidType, 0, 0, "D");
    EXPECT_TRUE(std::dynamic_pointer_cast<Druid>(n2) != nullptr);
    
    auto n3 = factory(ElfType, 0, 0, "E");
    EXPECT_TRUE(std::dynamic_pointer_cast<Elf>(n3) != nullptr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}