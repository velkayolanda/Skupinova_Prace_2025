	#ifndef LOOT_H
#define LOOT_H

#include <vector>
#include <string>


struct Item {
	std::string name;
	int combatBonus;      // Bonus pridany ku hodu kockou
	int value;            // Gold value
	std::string type;     // "zbrane", "armour", "potecka", "treasure"
};

// Načte všechny itemy ze souboru
std::vector<Item> loadLootTable(const std::string& filename);

// Vygeneruje náhodný loot z tabulky
Item getRandomLoot(const std::vector<Item>& lootTable);

// Vygeneruje náhodný loot podle typu (weapon, armor, potion, treasure)
Item getRandomLootByType(const std::vector<Item>& lootTable, const std::string& type);

// Vygeneruje náhodný loot podle tier/hodnoty (pro různě cenné místnosti)
Item getRandomLootByValue(const std::vector<Item>& lootTable, int minValue, int maxValue);

// Šance na spawn lootu v místnosti (vrátí true pokud má dropnout loot)
bool rollForLoot(int chancePercent = 50);

// Inicializuje globální loot tabulku (zavolej na začátku hry)
void initLootSystem(const std::string& filename);

// Získá náhodný loot z globální tabulky (nemusíš pokaždé předávat vector)
Item getRandomLootGlobal();
Item getRandomLootByTypeGlobal(const std::string& type);
Item getRandomLootByValueGlobal(int minValue, int maxValue);
#endif // LOOT_H