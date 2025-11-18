//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#ifndef SKUPINOVA_PRACE_2025_COMBAT_H
#define SKUPINOVA_PRACE_2025_COMBAT_H


#include "enemy_types.h"
#include "loot.h"
#include <vector>
#include <string>

class Combat {
private:
    std::vector<Item>& playerInventory;
    int playerGold;

    int rollD20();
    int calculateTotalCombatBonus();
    void displayCombatStart(const Enemy& enemy);
    void displayRollResult(int roll, int bonus, int total, const std::string& context);

public:
    Combat(std::vector<Item>& inventory, int& gold);

    // Main combat function - returns true if player wins
    bool fight(Enemy& enemy);

    // Handle loot after winning
    void collectLoot(const Enemy& enemy);
};

#endif //SKUPINOVA_PRACE_2025_COMBAT_H