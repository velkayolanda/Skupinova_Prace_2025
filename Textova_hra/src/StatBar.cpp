//
// Created by sevci on 22.11.2025.
//

#include "StatBar.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Konstruktor
StatBar::StatBar(int initialHealth, int initialGold)
        : health(initialHealth), gold(initialGold) {}

// Health
int StatBar::getHealth() const {
    return health;
}

void StatBar::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void StatBar::heal(int amount) {
    health += amount;
}

// Gold
int StatBar::getGold() const {
    return gold;
}

void StatBar::addGold(int amount) {
    gold += amount;
}

// Inventory
const std::vector<Item>& StatBar::getInventory() const {
    return inventory;
}

void StatBar::addItem(const Item& item) {
    inventory.push_back(item);
}

// Combat bonus
int StatBar::getCombatBonus() const {
    int bonus = 0;
    for (const auto& item : inventory) {
        bonus += item.combatBonus;
    }
    return bonus;
}