//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#include "combat.h"
#include <iostream>
#include "dice_roll.h"

// Inicializace statických proměnných
int Combat::enemy_damage = 0;
int Combat::last_player_roll = 0;
int Combat::last_player_bonus = 0;
int Combat::last_player_total = 0;
int Combat::last_enemy_roll = 0;
int Combat::last_enemy_bonus = 0;
int Combat::last_enemy_total = 0;
bool Combat::last_battle_won = false;

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
    //std::cout << "Narazil jsi na " << enemy.name << "!\n";
    //std::cout << enemy.description << "\n";
    //std::cout << "Enemakova obtiznost: " << enemy.difficultyNumber << "\n";
}

// Zobrazeni hodu
void Combat::displayRollResult(int roll, int bonus, int total, const std::string& context) {
    //std::cout << context << ": Hod " << roll
      //        << " + Bonus " << bonus
        //      << " = Total " << total << "\n";
}

// Hlavni boj
bool Combat::fight(Enemy& enemy) {
    displayCombatStart(enemy);

    int playerRoll = rollD20();
    int playerBonus = calculateTotalCombatBonus();
    int playerTotal = playerRoll + playerBonus;

    int enemyRoll = rollD20();
    int enemyBonus = enemy.difficultyNumber;
    int enemyTotal = 0 + enemyBonus;

    // ULOŽENÍ VÝSLEDKŮ do statických proměnných
    last_player_roll = playerRoll;
    last_player_bonus = playerBonus;
    last_player_total = playerTotal;
    last_enemy_roll = enemyRoll;
    last_enemy_bonus = enemyBonus;
    last_enemy_total = enemyTotal;

    displayRollResult(playerRoll, playerBonus, playerTotal, "Player");
    displayRollResult(enemyRoll, enemyBonus, enemyTotal, "Enemy");

    if (playerTotal >= enemyTotal) {
        //std::cout << "Vyhrals!\n";
        last_battle_won = true;
        collectLoot(enemy);
        return true;
    } else {
        int damage = enemy.difficultyNumber;
        playerStats.takeDamage(damage);
        Combat::enemy_damage = damage;
        //std::cout << "Prohrals! Dostals " << damage << " damage.\n";
        last_battle_won = false;
        return false;
    }
}

// Loot
void Combat::collectLoot(const Enemy& enemy) {
    // Přidej zlato
    playerStats.addGold(enemy.goldReward);
    //std::cout << "Získals " << enemy.goldReward << " zlata!\n";

    // Pokud má nepřítel možný loot
    if (!enemy.possibleLootNames.empty()) {
        //std::cout << "[DEBUG] Získávám loot...\n";
        Item loot = getEnemyLootDrop(enemy);
        //std::cout << "[DEBUG] Loot získán: " << loot.name << "\n";

        // Kontrola, jestli není "Nothing"
        if (loot.name != "Nothing" && loot.type != "empty") {
            playerStats.addItem(loot);

          //  std::cout << "Dostals loot: " << loot.name
            //          << " (+" << loot.combatBonus << " combat bonus)\n";

        }
    }
}