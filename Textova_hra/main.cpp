#include <iostream>
#include "src/dice_roll.h"

int main() {
    std::cout << "Rolling a d20 (1-20):\n";

    for (int i = 0; i < 5; ++i) {
        int result = rollDice(20);
        std::cout << "Roll " << (i + 1) << ": " << result << "\n";
    }

    std::cout << "\nRolling 3d20:\n";
    int multiRoll = rollMultipleDice(3, 20);
    std::cout << "Total: " << multiRoll << "\n";

    return 0;
}