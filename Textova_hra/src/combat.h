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
    int calculateTotalCombatBonus();
    void displayCombatStart(const Enemy& enemy);
    void displayRollResult(int roll, int bonus, int total, const std::string& context);

public:
    Combat(StatBar& stats);
    static int enemy_damage;
    // Hlavni funkce boje - vraci true, pokud hrác vyhraje
    bool fight(Enemy& enemy);

    // Loot po vyhre
    void collectLoot(const Enemy& enemy);
};

#endif //SKUPINOVA_PRACE_2025_COMBAT_H