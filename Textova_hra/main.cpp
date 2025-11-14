#include <iostream>
#include <random>
#include <vector>
#include "src/dice_roll.h"
#include "src/enemy_types.h"

int main() {
    std::cout << "Testing dice roll system...\n";
    int roll = rollDice(20);
    std::cout << "Rolled d20: " << roll << "\n\n";

    std::cout << "Testing enemy system...\n";
    auto enemies = getAllEnemies();
    std::cout << "Total enemies loaded: " << enemies.size() << "\n";

    std::cout << "\nTesting random enemy generation...\n";
    for (int tier = 1; tier <= 4; tier++) {
        Enemy enemy = getRandomEnemy(tier);
        std::cout << "Tier " << tier << ": " << enemy.name << " (difficulty " << enemy.difficultyNumber << ")\n";
    }

    std::cout << "\nTesting item system...\n";
    auto items = getAllItems();
    std::cout << "Total items loaded: " << items.size() << "\n";

    std::cout << "\nTesting combat bonus calculation...\n";
    std::vector<Item> testInventory = {items[1], items[6]}; // Short Sword + Chainmail
    int bonus = calculateCombatBonus(testInventory);
    std::cout << "Combat bonus with Short Sword and Chainmail: +" << bonus << "\n";

    std::cout << "\n=== COMPLETE ===\n";

    return 0;
}