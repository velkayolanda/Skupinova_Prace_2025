//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#ifndef SKUPINOVA_PRACE_2025_INVENTORY_H
#define SKUPINOVA_PRACE_2025_INVENTORY_H

#include <string>
#include <vector>
#include <optional>
#include "loot.h"  // Použijeme globální Item strukturu

class inventory {
public:
    // Používáme ENUM pro typy předmětů v inventáři
    enum class ItemType { Weapon, Potion, Armor, Misc };

    // Interní struktura pro inventář s množstvím
    struct InventoryItem {
        std::string name;
        ItemType type;
        int quantity{1};
        int combatBonus{0};
        int value{0};

        InventoryItem() = default;
        InventoryItem(std::string n, ItemType t, int q = 1, int cb = 0, int v = 0)
            : name(std::move(n)), type(t), quantity(q), combatBonus(cb), value(v) {}
    };

    // Constructor sets slot limits
    inventory(int maxWeapons = 2, int maxPotions = 5, int maxArmors = 2, int equipSlots = 2);

    // Inventory operations
    bool addItem(const InventoryItem& item);
    bool removeItem(const std::string& name, int qty = 1);

    // Equip/unequip
    bool equipItem(const std::string& name, int slot = 0);
    bool unequip(int slot);

    // Gold management
    void addGold(int amount);
    bool spendGold(int amount);
    int getGold() const;

    // Display
    void display() const;

    // Add loot from global loot system (::Item from loot.h)
    bool addLoot(const ::Item& loot);
    bool addLoot(const std::vector<::Item>& loot);

    // Accessors
    int maxWeapons() const { return maxWeapons_; }
    int maxPotions() const { return maxPotions_; }
    int maxArmors() const { return maxArmors_; }
    int equipSlots() const { return equipSlots_; }

private:
    int maxWeapons_;
    int maxArmors_;
    int maxPotions_;
    int equipSlots_;

    std::vector<InventoryItem> weapons_;
    std::vector<InventoryItem> armors_;
    std::vector<InventoryItem> potions_;
    std::vector<InventoryItem> misc_;
    std::vector<std::optional<InventoryItem>> equipped_;

    int gold_{0};

    // Helpers
    int findIndexByName(std::vector<InventoryItem>& container, const std::string& name);
    int findIndexByNameConst(const std::vector<InventoryItem>& container, const std::string& name) const;
};

#endif //SKUPINOVA_PRACE_2025_INVENTORY_H