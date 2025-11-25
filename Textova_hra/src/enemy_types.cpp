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

    // TIER 1 - Snadni nepratele
    Enemy rat;
    rat.name = "Obrovska krysa";
    rat.difficultyNumber = 8;
    rat.goldReward = 5;
    rat.tier = 1;
    rat.possibleLootNames = {"Rezava dyka","Zlataky"};
    rat.description = "Obrovska krysa s rude zaricima ocima.";
    enemies.push_back(rat);

    Enemy goblin;
    goblin.name = "Goblin pruzkumnik";
    goblin.difficultyNumber = 9;
    goblin.goldReward = 8;
    goblin.tier = 1;
    goblin.possibleLootNames = {"Rezava dyka","Kratky mec"};
    goblin.description = "Maly zeleny skret s primitivnim kyjem.";
    enemies.push_back(goblin);

    Enemy skeleton;
    skeleton.name = "Padly valecnik";
    skeleton.difficultyNumber = 10;
    skeleton.goldReward = 10;
    skeleton.tier = 1;
    skeleton.possibleLootNames = {"Kratky mec", "Kozena vesta"};
    skeleton.description = "Ozivly kostlivec ozbrojeny rezavymi zbranemi.";
    enemies.push_back(skeleton);

    Enemy wolf;
    wolf.name = "Divoky vlk";
    wolf.difficultyNumber = 9;
    wolf.goldReward = 7;
    wolf.tier = 1;
    wolf.possibleLootNames = {"Kozena vesta", "Zlataky"};
    wolf.description = "Hladovy vlk s ostrymi tesaky.";
    enemies.push_back(wolf);

    // TIER 2 - Stredny nepratele
    Enemy orc;
    orc.name = "Rabujici Orc";
    orc.difficultyNumber = 12;
    orc.goldReward = 20;
    orc.tier = 2;
    orc.possibleLootNames = {"Bojova sekera","Krouzkova zbroj"};
    orc.description = "Brutalni orksky valecnik pokryty bitevnimi jizvami.";
    enemies.push_back(orc);

    Enemy mage;
    mage.name = "Temny carodej";
    mage.difficultyNumber = 13;
    mage.goldReward = 25;
    mage.tier = 2;
    mage.possibleLootNames = {"Magicky posilena cepel","Elixir sily"};
    mage.description = "Postava halena v rouchu obklopena praskajici temnou magii.";
    enemies.push_back(mage);

    Enemy knight;
    knight.name = "Zaklety rytir";
    knight.difficultyNumber = 14;
    knight.goldReward = 30;
    knight.tier = 2;
    knight.possibleLootNames = {"Bojova sekera","Ocelove brneni"};
    knight.description = "Padly rytir spoutany temnou magii.";
    enemies.push_back(knight);

    Enemy spider;
    spider.name = "Obrovksy pavouk";
    spider.difficultyNumber = 12;
    spider.goldReward = 18;
    spider.tier = 2;
    spider.possibleLootNames = {"Kratky mec","Stribrny pohar"};
    spider.description = "Obrovsky pavoukovec s jedovatymi tesaky.";
    enemies.push_back(spider);

    Enemy bandit;
    bandit.name = "Vudce banditu";
    bandit.difficultyNumber = 13;
    bandit.goldReward = 22;
    bandit.tier = 2;
    bandit.possibleLootNames = {"Bojova sekera", "Stribrny pohar"};
    bandit.description = "Lstivy zlodej a vudce zdejsich zlocincu.";
    enemies.push_back(bandit);

    // TIER 3 - Tezci nepratele
    Enemy troll;
    troll.name = "Berserker troll";
    troll.difficultyNumber = 16;
    troll.goldReward = 40;
    troll.tier = 3;
    troll.possibleLootNames = {"Magicky posilena cepel","Ocelove brneni","Staroveky drahokam"};
    troll.description = "Obrovsky troll s neuveritelnymi regeneracnimi schopnostmi.";
    enemies.push_back(troll);

    Enemy vampire;
    vampire.name = "Pan upiru";
    vampire.difficultyNumber = 17;
    vampire.goldReward = 50;
    vampire.tier = 3;
    vampire.possibleLootNames = {"Legendarni mec", "Zbroj z dracich supin"};
    vampire.description = "Staroveky upir s hypnotickymi schopnostmi.";
    enemies.push_back(vampire);

    Enemy golem;
    golem.name = "Kamenny golem";
    golem.difficultyNumber = 18;
    golem.goldReward = 45;
    golem.tier = 3;
    golem.possibleLootNames = {"Magicky posilena cepel","Ocelove brneni"};
    golem.description = "Masivni stvoreni z ziveho kamene.";
    enemies.push_back(golem);

    Enemy assassin;
    assassin.name = "Tajemny vrah";
    assassin.difficultyNumber = 16;
    assassin.goldReward = 42;
    assassin.tier = 3;
    assassin.possibleLootNames = {"Magicky posilena cepel", "Elixir hrdiny"};
    assassin.description = "Smrtici zabijak utocici ze stinu noci.";
    enemies.push_back(assassin);

    // TIER 4 - Boss enemies
    Enemy dragon;
    dragon.name = "Staroveky drak";
    dragon.difficultyNumber = 20;
    dragon.goldReward = 100;
    dragon.tier = 4;
    dragon.possibleLootNames = {"Legendarni mec", "Zbroj z dracich supin","Draci poklad"};
    dragon.description = "Legendarni drak se supinami jako ocel.";
    enemies.push_back(dragon);

    Enemy demon;
    demon.name = "Kral demonu";
    demon.difficultyNumber = 22;
    demon.goldReward = 120;
    demon.tier = 4;
    demon.possibleLootNames = {"Legendarni mec","Zbroj z dracich supin","Draci poklad"};
    demon.description = "Vladce podsveti zahaleny v plamenech.";
    enemies.push_back(demon);

    Enemy lich;
    lich.name = "Mocny nemrtvi carodej";
    lich.difficultyNumber = 21;
    lich.goldReward = 110;
    lich.tier = 4;
    lich.possibleLootNames = {"Legendarni mec","Zbroj z dracich supin", "Draci poklad"};
    lich.description = "Carodej, ktery dosahl na vecny zivot.";
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
        // Zbrane
        {"Rezava dyka", 1, 5, "zbran"},
        {"Kratky mec", 2, 15, "zbran"},
        {"Bojova sekera", 3, 30, "zbran"},
        {"Magicky posilena cepel", 4, 50, "zbran"},
        {"Legendarni mec", 5, 100, "zbran"},

        // Zbroj
        {"Kozena vesta", 1, 10, "zbroj"},
        {"Krouzkova zbroj", 2, 25, "zbroj"},
        {"Ocelove brneni", 3, 45, "zbroj"},
        {"Zbroj z dracich supin", 4, 80, "zbroj"},

        // Potecka
        {"Elixir sily", 2, 20, "potecko"},
        {"Elixir hrdiny", 3, 35, "potecko"},

        // Treasures
        {"Zlataky", 0, 10, "trezor"},
        {"Stribrny pohar", 0, 25, "trezor"},
        {"Staroveky drahokam", 0, 50, "trezor"},
        {"Draci poklad", 0, 100, "trezor"}
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
        fallback.name = "Krysa";
        fallback.difficultyNumber = 8;
        fallback.goldReward = 5;
        fallback.tier = 1;
        fallback.possibleLootNames = {"Rezava dyka"};
        fallback.description = "Bezna krysa.";
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
        return {"Nic", 0, 0, "prazdne"};
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

    return {"Nic", 0, 0, "prazdne"};
}