#include "loot.h"
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>

// Globální loot tabulka
static std::vector<Item> globalLootTable;

std::vector<Item> loadLootTable(const std::string& filename) {
    std::vector<Item> items;
    std::ifstream file(filename);

    if (!file.is_open()) {
        // Pokud soubor neexistuje, vrať prázdný vector
        return items;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Přeskoč prázdné řádky a komentáře
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string name, type;
        int combatBonus, value;

        // Parsuj CSV: name,combatBonus,value,type
        std::getline(ss, name, ',');
        ss >> combatBonus;
        ss.ignore();
        ss >> value;
        ss.ignore();
        std::getline(ss, type);

        items.push_back({name, combatBonus, value, type});
    }

    file.close();
    return items;
}

Item getRandomLoot(const std::vector<Item>& lootTable) {
    if (lootTable.empty()) {
        return {"Nothing", 0, 0, "empty"};
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, lootTable.size() - 1);

    return lootTable[dist(gen)];
}

Item getRandomLootByType(const std::vector<Item>& lootTable, const std::string& type) {
    std::vector<Item> filtered;

    for (const auto& item : lootTable) {
        if (item.type == type) {
            filtered.push_back(item);
        }
    }

    if (filtered.empty()) {
        return {"Nothing", 0, 0, "empty"};
    }

    return getRandomLoot(filtered);
}

Item getRandomLootByValue(const std::vector<Item>& lootTable, int minValue, int maxValue) {
    std::vector<Item> filtered;

    for (const auto& item : lootTable) {
        if (item.value >= minValue && item.value <= maxValue) {
            filtered.push_back(item);
        }
    }

    if (filtered.empty()) {
        return {"Nothing", 0, 0, "empty"};
    }

    return getRandomLoot(filtered);
}

bool rollForLoot(int chancePercent) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    return dist(gen) <= chancePercent;
}

void initLootSystem(const std::string& filename) {
    globalLootTable = loadLootTable(filename);
}

Item getRandomLootGlobal() {
    return getRandomLoot(globalLootTable);
}

Item getRandomLootByTypeGlobal(const std::string& type) {
    return getRandomLootByType(globalLootTable, type);
}

Item getRandomLootByValueGlobal(int minValue, int maxValue) {
    return getRandomLootByValue(globalLootTable, minValue, maxValue);
}