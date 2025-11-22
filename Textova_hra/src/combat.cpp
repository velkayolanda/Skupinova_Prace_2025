//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#include "combat.h"
#include <iostream>

#include "dice_roll.h"

Combat::Combat(StatBar& stats) : playerStats(stats) {}

// Hod D20
int Combat::rollD20() {
    return rollDice(20);
}

// Soucet bonusu hrace
int Combat::calculateTotalCombatBonus() {
    return playerStats.getCombatBonus();
}

// Zobrazeni zacatku boje
void Combat::displayCombatStart(const Enemy& enemy) {
    std::cout << "Narazil jsi na " << enemy.name << "!\n";
    std::cout << enemy.description << "\n";
    std::cout << "Enemakova obtiznost: " << enemy.difficultyNumber << "\n";
}

// Zobrazeni hodu
void Combat::displayRollResult(int roll, int bonus, int total, const std::string& context) {
    std::cout << context << ": Hod " << roll
              << " + Bonus " << bonus
              << " = Total " << total << "\n";
}

// Hlavni boj
bool Combat::fight(Enemy& enemy) {
    displayCombatStart(enemy);

    int playerRoll = rollD20();
    int playerTotal = playerRoll + calculateTotalCombatBonus();
    displayRollResult(playerRoll, calculateTotalCombatBonus(), playerTotal, "Player");

    int enemyRoll = rollD20();
    int enemyTotal = enemyRoll + enemy.difficultyNumber;
    displayRollResult(enemyRoll, enemy.difficultyNumber, enemyTotal, "Enemy");

    if (playerTotal >= enemyTotal) {
        std::cout << "Vyhrals!\n";
        collectLoot(enemy);
        return true;
    } else {
        int damage = enemy.difficultyNumber; // Jednoduchá logika damage
        playerStats.takeDamage(damage);
        std::cout << "Prohrals! Dostals " << damage << " damage.\n";
        return false;
    }
}

// Loot
void Combat::collectLoot(const Enemy& enemy) {
    playerStats.addGold(enemy.goldReward);

    if (!enemy.possibleLootNames.empty()) {
        Item loot = getEnemyLootDrop(enemy);
        playerStats.addItem(loot);
        std::cout << "Dostals loot: " << loot.name << "\n";
    }
}
