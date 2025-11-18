#include <iostream>
#include <random>
#include <vector>
#include "src/dice_roll.h"
#include "src/enemy_types.h"
#include "src/combat.h"

int main() {
    // 0. TEST: Kocka
    std::cout << "=== TEST KOCKY ===\n";
    std::cout << "Hadzanie d20 (5x):\n";
    for (int i = 1; i <= 5; i++) {
        int roll = rollDice(20);
        std::cout << "Hod " << i << ": " << roll << "\n";
    }

    std::cout << "\nHadzanie 3d20:\n";
    int multiRoll = rollMultipleDice(3, 20);
    std::cout << "Sucet: " << multiRoll << "\n";

    std::cout << "\n";

    // 1. Na zaciatku hry inicializovat loot system
    initLootSystem("data/loot_table.txt");

    std::cout << "=== LOOT SYSTEM TEST ===\n\n";

    // 2a. TEST: Pouzitie v miestnosti:
    std::cout << "--- Vstupil si do miestnosti ---\n";
    if (rollForLoot(70)) {  // 70% sanca na loot
        Item loot = getRandomLootGlobal();
        std::cout << "Nasiel si: " << loot.name << " (+" << loot.combatBonus
                  << " combat, " << loot.value << " gold)\n";
    } else {
        std::cout << "Miestnost je prazdna.\n";
    }

    // 2b. TEST: Loot podla typu (truhla so zbranami)
    std::cout << "\n--- Otvoril si zbrojnu truhlu ---\n";
    Item weapon = getRandomLootByTypeGlobal("weapon");
    std::cout << "Ziskal si zbran: " << weapon.name << "\n";

    // 2c. TEST: Loot podla hodnoty (mensie miestnosti = horsi loot)
    std::cout << "\n--- Mala pokladnicka ---\n";
    Item cheapLoot = getRandomLootByValueGlobal(5, 25);  // Itemy 5-25 gold
    std::cout << "Nasiel si: " << cheapLoot.name << "\n";

    // 2d. TEST: Velka miestnost -> vela lootu
    std::cout << "\n--- Dracia pokladnica ---\n";
    Item expensiveLoot = getRandomLootByValueGlobal(50, 100);  // Itemy 50-100 gold
    std::cout << "Ziskal si: " << expensiveLoot.name << "\n";

    // 3. TEST: nacitanie tabulky a prevod:
    std::vector<Item> customTable = loadLootTable("data/loot_table.txt");
    std::cout << "\n--- Vlastna tabulka ---\n";
    Item customLoot = getRandomLoot(customTable);
    std::cout << "Random item: " << customLoot.name << "\n";

    // 4. TEST: Simulacia ingame roomky:
    std::cout << "\n\n=== SIMULACE 5 MIESTNOSTI ===\n";
    for (int room = 1; room <= 5; room++) {
        std::cout << "\nMiestnost " << room << ": ";

        if (rollForLoot(50)) {
            // Rozne sance podla typu miestnosti
            if (room <= 2) {
                // horsie miestnosti
                Item item = getRandomLootByValueGlobal(0, 20);
                std::cout << "Nasiel si " << item.name;
            } else if (room <= 4) {
                // mid miestnosti
                Item item = getRandomLootByValueGlobal(15, 50);
                std::cout << "Nasiel si " << item.name;
            } else {
                // Boss miestnosti - top loot
                Item item = getRandomLootByValueGlobal(50, 100);
                std::cout << "Nasiel si " << item.name << " !!!";
            }
        } else {
            std::cout << "Prazdna";
        }
    }

    std::cout << "\n\n=== LOOT SYSTEM FUNKCNY! ===\n";

    // 5. TEST: COMBAT SYSTEM
    std::cout << "\n\n";
    std::cout << "========================================\n";
    std::cout << "       TEST BOJOVEHO SYSTEMU            \n";
    std::cout << "========================================\n\n";

    // Inicializuj hraca
    std::vector<Item> playerInventory;
    int playerGold = 50;

    // Vytvor bojovy system
    Combat combat(playerInventory, playerGold);

    std::cout << "Zakladny test - bez vybavenia:\n";
    std::cout << "Stlac Enter pre pokracovanie...\n";
    std::cin.get();

    // Test 1: Jednoduchy nepriatela (Tier 1)
    std::cout << "\n--- TEST 1: Tier 1 nepriatela ---\n";
    Enemy rat = getRandomEnemy(1);
    bool victory1 = combat.fight(rat);

    if (victory1) {
        std::cout << "\nAktualny inventar po boji:\n";
        std::cout << "Zlato: " << playerGold << "\n";
        std::cout << "Predmety (" << playerInventory.size() << "):\n";
        for (const auto& item : playerInventory) {
            std::cout << "  - " << item.name << " (+" << item.combatBonus << ")\n";
        }
    }

    // Test 2: Stredne tazky nepriatela (Tier 2)
    std::cout << "\n\n--- TEST 2: Tier 2 nepriatela ---\n";
    std::cout << "Stlac Enter pre pokracovanie...\n";
    std::cin.get();

    Enemy orc = getRandomEnemy(2);
    bool victory2 = combat.fight(orc);

    if (victory2) {
        std::cout << "\nAktualny inventar:\n";
        std::cout << "Zlato: " << playerGold << "\n";
        std::cout << "Predmety (" << playerInventory.size() << "):\n";
        for (const auto& item : playerInventory) {
            std::cout << "  - " << item.name << " (+" << item.combatBonus << ")\n";
        }
    }

    // Test 3: Tazky nepriatela (Tier 3)
    std::cout << "\n\n--- TEST 3: Tier 3 nepriatela ---\n";
    std::cout << "Stlac Enter pre pokracovanie...\n";
    std::cin.get();

    Enemy troll = getRandomEnemy(3);
    bool victory3 = combat.fight(troll);

    if (victory3) {
        std::cout << "\nAktualny inventar:\n";
        std::cout << "Zlato: " << playerGold << "\n";
        std::cout << "Predmety (" << playerInventory.size() << "):\n";
        for (const auto& item : playerInventory) {
            std::cout << "  - " << item.name << " (+" << item.combatBonus << ")\n";
        }
    }

    // Test 4: Boss (Tier 4) - len ak hrac ma dost vybavenia
    if (playerInventory.size() >= 2) {
        std::cout << "\n\n--- TEST 4: BOSS FIGHT (Tier 4) ---\n";
        std::cout << "Stlac Enter pre pokracovanie...\n";
        std::cin.get();

        Enemy boss = getRandomEnemy(4);
        bool victory4 = combat.fight(boss);

        if (victory4) {
            std::cout << "\n*** GRATULUJEM! Porazil si bossa! ***\n";
        }
    }

    // Finalny inventar
    std::cout << "\n\n";
    std::cout << "========================================\n";
    std::cout << "         FINALNY INVENTAR               \n";
    std::cout << "========================================\n";
    std::cout << "\nZlato: " << playerGold << "\n";
    std::cout << "Celkovy bojovy bonus: +" << calculateCombatBonus(playerInventory) << "\n";
    std::cout << "\nPredmety (" << playerInventory.size() << "):\n";

    if (playerInventory.empty()) {
        std::cout << "  (Ziadne predmety)\n";
    } else {
        for (const auto& item : playerInventory) {
            std::cout << "  - " << item.name << " (+" << item.combatBonus
                      << " combat, " << item.value << " gold, " << item.type << ")\n";
        }
    }

    std::cout << "\n=== COMBAT SYSTEM FUNKCNY! ===\n";
    return 0;
}