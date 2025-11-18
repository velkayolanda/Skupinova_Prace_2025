//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#include "combat.h"
#include <iostream>
#include <random>
#include <algorithm>

Combat::Combat(std::vector<Item>& inventory, int& gold)
    : playerInventory(inventory), playerGold(gold) {}

int Combat::rollD20() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 20);
    return dist(gen);
}

int Combat::calculateTotalCombatBonus() {
    return calculateCombatBonus(playerInventory);
}

void Combat::displayCombatStart(const Enemy& enemy) {
    std::cout << "\n========================================\n";
    std::cout << "           BOJ SA ZACINA!               \n";
    std::cout << "========================================\n";
    std::cout << "\nObjavil sa " << enemy.name << "!\n";
    std::cout << enemy.description << "\n";
    std::cout << "\nObtiaznost: " << enemy.difficultyNumber << "\n";
    std::cout << "Odmena: " << enemy.goldReward << " zlata\n";
    std::cout << "\n----------------------------------------\n";
}

void Combat::displayRollResult(int roll, int bonus, int total, const std::string& context) {
    std::cout << "\n" << context << ":\n";
    std::cout << "  Hod kockou: " << roll << "\n";
    std::cout << "  Bojovy bonus: +" << bonus << "\n";
    std::cout << "  --------------\n";
    std::cout << "  Celkom: " << total << "\n";
}

bool Combat::fight(Enemy& enemy) {
    displayCombatStart(enemy);

    // Zobraz hracacovu vybavu
    int bonus = calculateTotalCombatBonus();
    std::cout << "\nTvoja vybava:\n";
    if (playerInventory.empty()) {
        std::cout << "  Ziadne predmety (Bonus: +0)\n";
    } else {
        for (const auto& item : playerInventory) {
            if (item.combatBonus > 0) {
                std::cout << "  - " << item.name << " (+" << item.combatBonus << ")\n";
            }
        }
        std::cout << "  Celkovy bojovy bonus: +" << bonus << "\n";
    }

    std::cout << "\nStlac Enter pre hod kockou...";
    std::cin.ignore();
    std::cin.get();

    // Hod kockou
    int diceRoll = rollD20();
    int totalRoll = diceRoll + bonus;

    displayRollResult(diceRoll, bonus, totalRoll, "Tvoj bojovy hod");

    // Kontrola ci hrac vyhral
    if (totalRoll >= enemy.difficultyNumber) {
        std::cout << "\n+--------------------------------------+\n";
        std::cout << "|          VITAZSTVO!                  |\n";
        std::cout << "+--------------------------------------+\n";
        std::cout << "\nPorazil si " << enemy.name << "!\n";
        std::cout << "Hodil si " << totalRoll << " vs obtiaznost " << enemy.difficultyNumber << "\n";

        // Zber korist
        collectLoot(enemy);

        return true;
    } else {
        std::cout << "\n+--------------------------------------+\n";
        std::cout << "|          PREHRA!                     |\n";
        std::cout << "+--------------------------------------+\n";
        std::cout << "\n" << enemy.name << " ta premohol!\n";
        std::cout << "Hodil si " << totalRoll << " ale potreboval si " << enemy.difficultyNumber << "\n";
        std::cout << "\nMusis utiec z tejto miestnosti!\n";

        return false;
    }
}

void Combat::collectLoot(const Enemy& enemy) {
    // Pridaj zlato
    playerGold += enemy.goldReward;
    std::cout << "\n[$] Nasiel si " << enemy.goldReward << " zlata! (Celkom: " << playerGold << ")\n";

    // Ziskaj tabulku predmetov
    auto allItems = getAllItems();

    // Hod na korist (70% sanca)
    if (rollForLoot(70)) {
        std::cout << "\n[*] Prehladavas korist...\n";

        // Ziskaj nahodny predmet z moznej koristi nepriateľa
        if (!enemy.possibleLootNames.empty()) {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, enemy.possibleLootNames.size() - 1);

            std::string lootName = enemy.possibleLootNames[dist(gen)];

            // Najdi predmet v tabulke
            auto it = std::find_if(allItems.begin(), allItems.end(),
                [&lootName](const Item& item) { return item.name == lootName; });

            if (it != allItems.end()) {
                playerInventory.push_back(*it);
                std::cout << "\n[+] Nasiel si: " << it->name << "!\n";
                std::cout << "   Typ: " << it->type << "\n";
                if (it->combatBonus > 0) {
                    std::cout << "   Bojovy bonus: +" << it->combatBonus << "\n";
                }
                std::cout << "   Hodnota: " << it->value << " zlata\n";
            }
        }
    } else {
        std::cout << "\n[-] Nenasiel si ziadnu dalsiu korist.\n";
    }

    std::cout << "\nStlac Enter pre pokracovanie...";
    std::cin.get();
}