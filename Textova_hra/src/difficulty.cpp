//
// Created by honzi on 25. 11. 2025.
//

#include "difficulty.h"
int DiceMax = 1;

void  setDifficultyEasy()
{
    DiceMax = 1;
}
void  setDifficultyMedium()
{
    DiceMax = 5;
}
void  setDifficultyHard()
{
    DiceMax = 10;
}
void  setDifficultyInsane()
{
    DiceMax = 20;
}