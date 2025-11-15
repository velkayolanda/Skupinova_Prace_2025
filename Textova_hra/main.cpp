#include <iostream>
#include <random>
#include <vector>
#include "src/dice_roll.h"
#include "src/enemy_types.h"

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
    return 0;
}