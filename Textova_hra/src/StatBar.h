//
// Created by sevci on 22.11.2025.
//

#ifndef STATBAR_H
#define STATBAR_H

#include <vector>
#include <string>
#include "loot.h"  // Pro Item strukturu

class StatBar {
private:
    int health;
    int gold;
    std::vector<Item> inventory;

public:
    // Konstruktor
    StatBar(int initialHealth, int initialGold);

    // Health metody
    int getHealth() const;
    void takeDamage(int amount);
    void heal(int amount);
    bool isAlive() const;  // NOVÁ METODA

    // Gold metody
    int getGold() const;
    void addGold(int amount);
    bool spendGold(int amount);  // NOVÁ METODA

    // Inventory metody
    const std::vector<Item>& getInventory() const;
    void addItem(const Item& item);
    bool removeItem(const std::string& itemName);  // NOVÁ METODA

    // Combat bonus
    int getCombatBonus() const;

    // Display
    void display() const;  // NOVÁ METODA
};

#endif // STATBAR_H