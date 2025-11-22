//
// Created by sevci on 22.11.2025.
//

#ifndef SKUPINOVA_PRACE_2025_STATBAR_H
#define SKUPINOVA_PRACE_2025_STATBAR_H

#include <vector>
#include "loot.h"

using namespace std;

class StatBar {
private:
    int health;
    int gold;
    std::vector<Item> inventory;

public:
    StatBar(int initialHealth = 100, int initialGold = 0);

    // Health
    int getHealth() const;
    void takeDamage(int amount);
    void heal(int amount);

    // Gold
    int getGold() const;
    void addGold(int amount);

    // Inventory
    const std::vector<Item>& getInventory() const;
    void addItem(const Item& item);

    // Combat bonus
    int getCombatBonus() const;
};

#endif //SKUPINOVA_PRACE_2025_STATBAR_H
