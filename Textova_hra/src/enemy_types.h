//
// Created by honzi on 7. 11. 2025.
//

#ifndef SKUPINOVA_PRACE_2025_ENEMY_TYPES_H
#define SKUPINOVA_PRACE_2025_ENEMY_TYPES_H

#include <string>
#include <vector>

struct Item {
    std::string name;
    int combatBonus;      // Bonus pridany ku hodu kockou
    int value;            // Gold value
    std::string type;     // "zbrane", "armour", "potecka", "treasure"
};

struct Enemy {
    std::string name;
    int difficultyNumber; // Pocet na co hrac musi hodit na kocke s bonusmi aby porazil enemaka
    int goldReward;       // Gold  reward z vyhry
    std::vector<Item> possibleLoot; // Itemy ktore je mozne ziskat po vyhre
    std::string description;
};

// Getter na vsetky typy enemakov
std::vector<Enemy> getAllEnemies();

// Getter na random enemaka podla tieru
Enemy getRandomEnemy(int tier); // 1=lahky, 2=medium, 3=tazky, 4=boss

// Geter na vsetky itemy
std::vector<Item> getAllItems();

// Vypocet celeho bonusu v combate
int calculateCombatBonus(const std::vector<Item>& inventory);


#endif //SKUPINOVA_PRACE_2025_ENEMY_TYPES_H