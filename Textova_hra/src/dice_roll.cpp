//
// Created by honzi on 7. 11. 2025.
//

#include "dice_roll.h"
#include <random>

int rollDice(int max_value) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, max_value);
    return dist(gen);
}

int rollMultipleDice(int num_dice, int max_value) {
    int sum = 0;
    for (int i = 0; i < num_dice; ++i) {
        sum += rollDice(max_value);
    }
    return sum;
}