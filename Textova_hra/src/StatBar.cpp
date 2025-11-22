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

// Health metody
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

bool StatBar::isAlive() const {
    return health > 0;
}

// Gold metody
int StatBar::getGold() const {
    return gold;
}

void StatBar::addGold(int amount) {
    gold += amount;
}

bool StatBar::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

// Inventory metody
const std::vector<Item>& StatBar::getInventory() const {
    return inventory;
}

void StatBar::addItem(const Item& item) {
    // Zkontroluj, jestli už máme tento item
    for (auto& existingItem : inventory) {
        if (existingItem.name == item.name) {
            // Item už existuje, nemusíme ho znovu přidat
            // (pokud chceš stackování, můžeš to upravit)
            return;
        }
    }
    inventory.push_back(item);
}

bool StatBar::removeItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == itemName) {
            inventory.erase(it);
            return true;
        }
    }
    return false;
}

// Combat bonus
int StatBar::getCombatBonus() const {
    int bonus = 0;
    for (const auto& item : inventory) {
        bonus += item.combatBonus;
    }
    return bonus;
}

// Display metoda
void StatBar::display() const {
    std::cout << "\n=== HRAC STATISTIKY ===\n";
    std::cout << "Zdravi: " << health << "\n";
    std::cout << "Zlato: " << gold << "\n";
    std::cout << "Combat Bonus: +" << getCombatBonus() << "\n";
    std::cout << "\nInventar (" << inventory.size() << " predmetov):\n";

    if (inventory.empty()) {
        std::cout << "  (prazdny)\n";
    } else {
        for (const auto& item : inventory) {
            std::cout << "  - " << item.name
                      << " (+" << item.combatBonus << " combat, "
                      << item.value << " gold, " << item.type << ")\n";
        }
    }
    std::cout << "=====================\n";
}