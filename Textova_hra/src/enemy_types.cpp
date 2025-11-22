//
// Created by honzi on 7. 11. 2025.
//
#include "enemy_types.h"
#include "loot.h"
#include <random>
#include <fstream>
#include <sstream>

// POMOCNÁ FUNKCE - vrací hardcoded enemies (bez volání loadEnemiesFromFile!)
std::vector<Enemy> getHardcodedEnemies() {
    std::vector<Enemy> enemies;

    // TIER 1 - Easy enemies
    Enemy rat;
    rat.name = "Giant Rat";
    rat.difficultyNumber = 8;
    rat.goldReward = 5;
    rat.tier = 1;
    rat.possibleLootNames = {"Rusty Dagger","Gold Coins"};
    rat.description = "A large diseased rat with glowing red eyes.";
    enemies.push_back(rat);

    Enemy goblin;
    goblin.name = "Goblin Scout";
    goblin.difficultyNumber = 9;
    goblin.goldReward = 8;
    goblin.tier = 1;
    goblin.possibleLootNames = {"Rusty Dagger","Short Sword"};
    goblin.description = "A small green goblin armed with a crude club.";
    enemies.push_back(goblin);

    Enemy skeleton;
    skeleton.name = "Skeleton Warrior";
    skeleton.difficultyNumber = 10;
    skeleton.goldReward = 10;
    skeleton.tier = 1;
    skeleton.possibleLootNames = {"Short Sword", "Leather Vest"};
    skeleton.description = "An animated skeleton wielding rusty weapons.";
    enemies.push_back(skeleton);

    Enemy wolf;
    wolf.name = "Wild Wolf";
    wolf.difficultyNumber = 9;
    wolf.goldReward = 7;
    wolf.tier = 1;
    wolf.possibleLootNames = {"Leather Vest", "Gold Coins"};
    wolf.description = "A hungry wolf with sharp fangs.";
    enemies.push_back(wolf);

    // TIER 2 - Medium enemies
    Enemy orc;
    orc.name = "Orc Marauder";
    orc.difficultyNumber = 12;
    orc.goldReward = 20;
    orc.tier = 2;
    orc.possibleLootNames = {"Battle Axe","Chainmail"};
    orc.description = "A brutish orc warrior covered in battle scars.";
    enemies.push_back(orc);

    Enemy mage;
    mage.name = "Dark Mage";
    mage.difficultyNumber = 13;
    mage.goldReward = 25;
    mage.tier = 2;
    mage.possibleLootNames = {"Enchanted Blade","Strength Potion"};
    mage.description = "A robed figure crackling with dark magic.";
    enemies.push_back(mage);

    Enemy knight;
    knight.name = "Cursed Knight";
    knight.difficultyNumber = 14;
    knight.goldReward = 30;
    knight.tier = 2;
    knight.possibleLootNames = {"Battle Axe","Steel Armor"};
    knight.description = "A fallen knight bound by dark magic.";
    enemies.push_back(knight);

    Enemy spider;
    spider.name = "Giant Spider";
    spider.difficultyNumber = 12;
    spider.goldReward = 18;
    spider.tier = 2;
    spider.possibleLootNames = {"Short Sword","Silver Goblet"};
    spider.description = "A massive arachnid with venomous fangs.";
    enemies.push_back(spider);

    Enemy bandit;
    bandit.name = "Bandit Leader";
    bandit.difficultyNumber = 13;
    bandit.goldReward = 22;
    bandit.tier = 2;
    bandit.possibleLootNames = {"Battle Axe", "Silver Goblet"};
    bandit.description = "A cunning thief who leads a band of outlaws.";
    enemies.push_back(bandit);

    // TIER 3 - Hard enemies
    Enemy troll;
    troll.name = "Troll Berserker";
    troll.difficultyNumber = 16;
    troll.goldReward = 40;
    troll.tier = 3;
    troll.possibleLootNames = {"Enchanted Blade","Steel Armor","Ancient Gem"};
    troll.description = "A massive troll with incredible regenerative powers.";
    enemies.push_back(troll);

    Enemy vampire;
    vampire.name = "Vampire Lord";
    vampire.difficultyNumber = 17;
    vampire.goldReward = 50;
    vampire.tier = 3;
    vampire.possibleLootNames = {"Legendary Sword", "Dragon Scale Armor"};
    vampire.description = "An ancient vampire with hypnotic powers.";
    enemies.push_back(vampire);

    Enemy golem;
    golem.name = "Stone Golem";
    golem.difficultyNumber = 18;
    golem.goldReward = 45;
    golem.tier = 3;
    golem.possibleLootNames = {"Enchanted Blade","Steel Armor"};
    golem.description = "A massive construct of living stone.";
    enemies.push_back(golem);

    Enemy assassin;
    assassin.name = "Shadow Assassin";
    assassin.difficultyNumber = 16;
    assassin.goldReward = 42;
    assassin.tier = 3;
    assassin.possibleLootNames = {"Enchanted Blade", "Hero's Elixir"};
    assassin.description = "A deadly killer who strikes from the shadows.";
    enemies.push_back(assassin);

    // TIER 4 - Boss enemies
    Enemy dragon;
    dragon.name = "Ancient Dragon";
    dragon.difficultyNumber = 20;
    dragon.goldReward = 100;
    dragon.tier = 4;
    dragon.possibleLootNames = {"Legendary Sword", "Dragon Scale Armor","Dragon's Hoard"};
    dragon.description = "A legendary dragon with scales like steel.";
    enemies.push_back(dragon);

    Enemy demon;
    demon.name = "Demon King";
    demon.difficultyNumber = 22;
    demon.goldReward = 120;
    demon.tier = 4;
    demon.possibleLootNames = {"Legendary Sword","Dragon Scale Armor","Dragon's Hoard"};
    demon.description = "The ruler of the underworld, wreathed in flames.";
    enemies.push_back(demon);

    Enemy lich;
    lich.name = "Lich Overlord";
    lich.difficultyNumber = 21;
    lich.goldReward = 110;
    lich.tier = 4;
    lich.possibleLootNames = {"Legendary Sword","Dragon Scale Armor", "Dragon's Hoard"};
    lich.description = "An undead sorcerer of immense power.";
    enemies.push_back(lich);

    return enemies;
}

std::vector<Enemy> loadEnemiesFromFile(const std::string& filename) {
    std::vector<Enemy> enemies;
    std::ifstream file(filename);

    if (!file.is_open()) {
        // Fallback na hardcoded enemies - OPRAVENO bez rekurze!
        return getHardcodedEnemies();
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        Enemy enemy;

        std::getline(ss, enemy.name, ',');
        ss >> enemy.difficultyNumber;
        ss.ignore();
        ss >> enemy.goldReward;
        ss.ignore();
        ss >> enemy.tier;
        ss.ignore();
        std::getline(ss, enemy.description, ',');

        std::string lootString;
        std::getline(ss, lootString);
        std::stringstream lootStream(lootString);
        std::string lootItem;
        while (std::getline(lootStream, lootItem, ':')) {
            enemy.possibleLootNames.push_back(lootItem);
        }

        enemies.push_back(enemy);
    }

    file.close();
    return enemies;
}

std::vector<Item> loadItemsFromFile(const std::string& filename) {
    std::vector<Item> items;
    std::ifstream file(filename);

    if (!file.is_open()) {
        return getAllItems();
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string name, type;
        int combatBonus, value;

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

std::vector<Item> getAllItems() {
    return {
        // Weapons
        {"Rusty Dagger", 1, 5, "weapon"},
        {"Short Sword", 2, 15, "weapon"},
        {"Battle Axe", 3, 30, "weapon"},
        {"Enchanted Blade", 4, 50, "weapon"},
        {"Legendary Sword", 5, 100, "weapon"},

        // Armor
        {"Leather Vest", 1, 10, "armor"},
        {"Chainmail", 2, 25, "armor"},
        {"Steel Armor", 3, 45, "armor"},
        {"Dragon Scale Armor", 4, 80, "armor"},

        // Potions
        {"Strength Potion", 2, 20, "potion"},
        {"Hero's Elixir", 3, 35, "potion"},

        // Treasures
        {"Gold Coins", 0, 10, "treasure"},
        {"Silver Goblet", 0, 25, "treasure"},
        {"Ancient Gem", 0, 50, "treasure"},
        {"Dragon's Hoard", 0, 100, "treasure"}
    };
}

std::vector<Enemy> getAllEnemies() {
    // Zkus načíst ze souboru
    std::vector<Enemy> enemies = loadEnemiesFromFile("data/enemies.txt");

    // loadEnemiesFromFile už vrací hardcoded enemies pokud soubor neexistuje
    return enemies;
}

Enemy getRandomEnemy(int tier) {
    auto enemies = getAllEnemies();
    std::vector<Enemy> tierEnemies;

    // Filter by tier
    for (const auto& enemy : enemies) {
        if (enemy.tier == tier) {
            tierEnemies.push_back(enemy);
        }
    }

    if (tierEnemies.empty()) {
        // Fallback na prvního nepřítele
        if (!enemies.empty()) return enemies[0];

        // Poslední fallback - vytvoř základního nepřítele
        Enemy fallback;
        fallback.name = "Rat";
        fallback.difficultyNumber = 8;
        fallback.goldReward = 5;
        fallback.tier = 1;
        fallback.possibleLootNames = {"Rusty Dagger"};
        fallback.description = "A simple rat.";
        return fallback;
    }

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

Item getEnemyLootDrop(const Enemy& enemy) {
    if (enemy.possibleLootNames.empty()) {
        return {"Nothing", 0, 0, "empty"};
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, enemy.possibleLootNames.size() - 1);

    int randomIndex = dist(gen);
    std::string selectedLootName = enemy.possibleLootNames[randomIndex];

    std::vector<Item> allItems = getAllItems();
    for (const auto& item : allItems) {
        if (item.name == selectedLootName) {
            return item;
        }
    }

    if (!allItems.empty()) {
        return allItems[0];
    }

    return {"Nothing", 0, 0, "empty"};
}