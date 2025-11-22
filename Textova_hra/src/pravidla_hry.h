//
// Created by Jar Jar Banton  on 7. 11. 2025. made by sevci
//

#ifndef SKUPINOVA_PRACE_2025_PRAVIDLA_HRY_H
#define SKUPINOVA_PRACE_2025_PRAVIDLA_HRY_H


#include <string>

// Pomaly výpis textu
void slowPrint(const std::string& text, int delayMs = 20);

void printIntro();

// Vypise pravidla ze souboru
void printRules(const std::string& filename);

// Spusti hlavni menu
void showMenu();



#endif //SKUPINOVA_PRACE_2025_PRAVIDLA_HRY_H