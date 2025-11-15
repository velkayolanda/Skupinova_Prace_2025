//
// Created by honzi on 7. 11. 2025.
//
#include "enemy_types.h"
#include "loot.h"
#include <random>
#include <fstream>
#include <sstream>

std::vector<Item> loadItemsFromFile(const std::string& filename) {
    std::vector<Item> items;
    std::ifstream file(filename);

    if (!file.is_open()) {
        // Fallback na hardcoded items pokud soubor neexistuje
        return getAllItems();
    }

    std::string line;
    while (std::getline(file, line)) {
        // Preskoc prazdne radky a komentare
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string name, type;
        int combatBonus, value;

        // Parsuj CSV format: name,combatBonus,value,type
        std::getline(ss, name, ',');
        ss >> combatBonus;
        ss.ignore(); // Preskoc carku
        ss >> value;
        ss.ignore(); // Preskoc carku
        std::getline(ss, type);

        items.push_back({name, combatBonus, value, type});
    }

    file.close();
    return items;
}

std::vector<Item> getAllItems() {
    return {
        // Zbrane
        {"Rusty Dagger", 1, 5, "weapon"},
        {"Short Sword", 2, 15, "weapon"},
        {"Battle Axe", 3, 30, "weapon"},
        {"Enchanted Blade", 4, 50, "weapon"},
        {"Legendary Sword", 5, 100, "weapon"},

        // Armour
        {"Leather Vest", 1, 10, "armor"},
        {"Chainmail", 2, 25, "armor"},
        {"Steel Armor", 3, 45, "armor"},
        {"Dragon Scale Armor", 4, 80, "armor"},

        // Potecka (jednorazove bonusy)
        {"Strength Potion", 2, 20, "potion"},
        {"Hero's Elixir", 3, 35, "potion"},

        // Poklady / Loot (bez pridanania combat vyhody iba gold hopdnoty)
        {"Gold Coins", 0, 10, "treasure"},
        {"Silver Goblet", 0, 25, "treasure"},
        {"Ancient Gem", 0, 50, "treasure"},
        {"Dragon's Hoard", 0, 100, "treasure"}
    };
}

std::vector<Enemy> getAllEnemies() {
    std::vector<Enemy> enemies;

    // TIER 1 - Lahky enemaci (potrebna 8-10 na kill)
    Enemy rat;
    rat.name = "Giant Rat";
    rat.difficultyNumber = 8;
    rat.goldReward = 5;
    rat.possibleLoot = {{"Rusty Dagger", 1, 5, "weapon"}, {"Gold Coins", 0, 10, "treasure"}};
    rat.description = "A large diseased rat with glowing red eyes.";
    enemies.push_back(rat);

    Enemy goblin;
    goblin.name = "Goblin Scout";
    goblin.difficultyNumber = 9;
    goblin.goldReward = 8;
    goblin.possibleLoot = {{"Rusty Dagger", 1, 5, "weapon"}, {"Short Sword", 2, 15, "weapon"}};
    goblin.description = "A small green goblin armed with a crude club.";
    enemies.push_back(goblin);

    Enemy skeleton;
    skeleton.name = "Skeleton Warrior";
    skeleton.difficultyNumber = 10;
    skeleton.goldReward = 10;
    skeleton.possibleLoot = {{"Short Sword", 2, 15, "weapon"}, {"Leather Vest", 1, 10, "armor"}};
    skeleton.description = "An animated skeleton wielding rusty weapons.";
    enemies.push_back(skeleton);

    Enemy wolf;
    wolf.name = "Wild Wolf";
    wolf.difficultyNumber = 9;
    wolf.goldReward = 7;
    wolf.possibleLoot = {{"Leather Vest", 1, 10, "armor"}, {"Gold Coins", 0, 10, "treasure"}};
    wolf.description = "A hungry wolf with sharp fangs.";
    enemies.push_back(wolf);

    // TIER 2 - Stredny enemaci (potrebna 12-14 na kill)
    Enemy orc;
    orc.name = "Orc Marauder";
    orc.difficultyNumber = 12;
    orc.goldReward = 20;
    orc.possibleLoot = {{"Battle Axe", 3, 30, "weapon"}, {"Chainmail", 2, 25, "armor"}};
    orc.description = "A brutish orc warrior covered in battle scars.";
    enemies.push_back(orc);

    Enemy mage;
    mage.name = "Dark Mage";
    mage.difficultyNumber = 13;
    mage.goldReward = 25;
    mage.possibleLoot = {{"Enchanted Blade", 4, 50, "weapon"}, {"Strength Potion", 2, 20, "potion"}};
    mage.description = "A robed figure crackling with dark magic.";
    enemies.push_back(mage);

    Enemy knight;
    knight.name = "Cursed Knight";
    knight.difficultyNumber = 14;
    knight.goldReward = 30;
    knight.possibleLoot = {{"Battle Axe", 3, 30, "weapon"}, {"Steel Armor", 3, 45, "armor"}};
    knight.description = "A fallen knight bound by dark magic.";
    enemies.push_back(knight);

    Enemy spider;
    spider.name = "Giant Spider";
    spider.difficultyNumber = 12;
    spider.goldReward = 18;
    spider.possibleLoot = {{"Short Sword", 2, 15, "weapon"}, {"Silver Goblet", 0, 25, "treasure"}};
    spider.description = "A massive arachnid with venomous fangs.";
    enemies.push_back(spider);

    Enemy bandit;
    bandit.name = "Bandit Leader";
    bandit.difficultyNumber = 13;
    bandit.goldReward = 22;
    bandit.possibleLoot = {{"Battle Axe", 3, 30, "weapon"}, {"Silver Goblet", 0, 25, "treasure"}};
    bandit.description = "A cunning thief who leads a band of outlaws.";
    enemies.push_back(bandit);

    // TIER 3 - tazky enemaci (potrebna 16-18 na poprazku)
    Enemy troll;
    troll.name = "Troll Berserker";
    troll.difficultyNumber = 16;
    troll.goldReward = 40;
    troll.possibleLoot = {{"Enchanted Blade", 4, 50, "weapon"}, {"Steel Armor", 3, 45, "armor"}, {"Ancient Gem", 0, 50, "treasure"}};
    troll.description = "A massive troll with incredible regenerative powers.";
    enemies.push_back(troll);

    Enemy vampire;
    vampire.name = "Vampire Lord";
    vampire.difficultyNumber = 17;
    vampire.goldReward = 50;
    vampire.possibleLoot = {{"Legendary Sword", 5, 100, "weapon"}, {"Dragon Scale Armor", 4, 80, "armor"}};
    vampire.description = "An ancient vampire with hypnotic powers.";
    enemies.push_back(vampire);

    Enemy golem;
    golem.name = "Stone Golem";
    golem.difficultyNumber = 18;
    golem.goldReward = 45;
    golem.possibleLoot = {{"Enchanted Blade", 4, 50, "weapon"}, {"Steel Armor", 3, 45, "armor"}};
    golem.description = "A massive construct of living stone.";
    enemies.push_back(golem);

    Enemy assassin;
    assassin.name = "Shadow Assassin";
    assassin.difficultyNumber = 16;
    assassin.goldReward = 42;
    assassin.possibleLoot = {{"Enchanted Blade", 4, 50, "weapon"}, {"Hero's Elixir", 3, 35, "potion"}};
    assassin.description = "A deadly killer who strikes from the shadows.";
    enemies.push_back(assassin);

    // TIER 4 - Boss (potrebna 20+ na kill)
    Enemy dragon;
    dragon.name = "Ancient Dragon";
    dragon.difficultyNumber = 20;
    dragon.goldReward = 100;
    dragon.possibleLoot = {{"Legendary Sword", 5, 100, "weapon"}, {"Dragon Scale Armor", 4, 80, "armor"}, {"Dragon's Hoard", 0, 100, "treasure"}};
    dragon.description = "A legendary dragon with scales like steel.";
    enemies.push_back(dragon);

    Enemy demon;
    demon.name = "Demon King";
    demon.difficultyNumber = 22;
    demon.goldReward = 120;
    demon.possibleLoot = {{"Legendary Sword", 5, 100, "weapon"}, {"Dragon Scale Armor", 4, 80, "armor"}, {"Dragon's Hoard", 0, 100, "treasure"}};
    demon.description = "The ruler of the underworld, wreathed in flames.";
    enemies.push_back(demon);

    Enemy lich;
    lich.name = "Lich Overlord";
    lich.difficultyNumber = 21;
    lich.goldReward = 110;
    lich.possibleLoot = {{"Legendary Sword", 5, 100, "weapon"}, {"Dragon Scale Armor", 4, 80, "armor"}, {"Dragon's Hoard", 0, 100, "treasure"}};
    lich.description = "An undead sorcerer of immense power.";
    enemies.push_back(lich);

    return enemies;
}

Enemy getRandomEnemy(int tier) {
    auto enemies = getAllEnemies();
    std::vector<Enemy> tierEnemies;

    // Filter na enemakov podla tieru
    if (tier == 1) {
        for (int i = 0; i < 4; i++) tierEnemies.push_back(enemies[i]);
    } else if (tier == 2) {
        for (int i = 4; i < 9; i++) tierEnemies.push_back(enemies[i]);
    } else if (tier == 3) {
        for (int i = 9; i < 13; i++) tierEnemies.push_back(enemies[i]);
    } else if (tier == 4) {
        for (int i = 13; i < 16; i++) tierEnemies.push_back(enemies[i]);
    }

    if (tierEnemies.empty()) return enemies[0];

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, tierEnemies.size() - 1);

    return tierEnemies[dist(gen)];
}

int calculateCombatBonus(const std::vector<Item>& inventory) {
    int bonus = 0;
    for (const auto& item : inventory) {
        bonus += item.combatBonus;
    }
    return bonus;
}