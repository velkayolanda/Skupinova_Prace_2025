//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#ifndef SKUPINOVA_PRACE_2025_COMBAT_H
#define SKUPINOVA_PRACE_2025_COMBAT_H

#include "enemy_types.h"
#include "loot.h"
#include "StatBar.h"
#include <vector>
#include <string>

class Combat {
private:
    StatBar& playerStats;

    int rollD20();
    int rollEnemy();
    int calculateTotalCombatBonus();
    void displayCombatStart(const Enemy& enemy);
    void displayRollResult(int roll, int bonus, int total, const std::string& context);

public:
    Combat(StatBar& stats);

    // Statické proměnné pro uložení výsledků posledního boje
    static int enemy_damage;
    static int last_player_roll;
    static int last_player_bonus;
    static int last_player_total;
    static int last_enemy_roll;
    static int last_enemy_bonus;
    static int last_enemy_total;
    static bool last_battle_won;

    // Hlavni funkce boje - vraci true, pokud hrác vyhraje
    bool fight(Enemy& enemy);

    // Loot po vyhre
    void collectLoot(const Enemy& enemy);
};

#endif //SKUPINOVA_PRACE_2025_COMBAT_H