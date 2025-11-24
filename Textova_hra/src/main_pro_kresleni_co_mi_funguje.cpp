#include "Kresleni.h"
#include <thread>
#include <chrono>
#include <conio.h>
#include <iostream>
#include <windows.h>
// int main() {
//     int* columns, *rows;
        columns = new int;
        rows = new int;

        Kresleni::ZiskaniVelikostiConsole(*columns, *rows);
        Kresleni kres(*columns-1,*rows-1);

        Mistnost mistnost(true);
        mistnost.VyberMistnost();

        kres.NacteniMistnosti(mistnost);
        std::string zdravi = std::to_string(playerStats.getHealth());
        std::string bonus = "+" + std::to_string(playerStats.getCombatBonus());
        std::string zlato = std::to_string(playerStats.getGold()) + " gold";
        std::string items = std::to_string(playerStats.getInventory().size()) + " items";
        Enemy orc = getRandomEnemy(2);

        kres.PsaniStat(zdravi, bonus, items, zlato);
        kres.PsaniEnemy(orc.name, orc.description);
        kres.VykresleniThread(kres);
        while (true) {
            if (GetAsyncKeyState(VK_LEFT)) {
                bool testD = false;
                for (int i = 0; i < mistnost.dvere.size(); i++) {
                    if (mistnost.dvere[i]=="D_Z") {
                        testD = true;
                    }
                }
                if (testD) {
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_V");
                    kres.NacteniMistnosti(mistnost);
                    kres.PsaniStat(zdravi, bonus, items, zlato);
                    kres.RozmisteniPredmetu(10);
                    kres.PsaniEnemy(orc.name , orc.description);
                    kres.VykresleniThread(kres);
                }
            }
            else if (GetAsyncKeyState(VK_RIGHT)) {
                bool testD = false;
                for (int i = 0; i < mistnost.dvere.size(); i++) {
                    if (mistnost.dvere[i]=="D_V") {
                        testD = true;
                    }
                }
                if (testD) {
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_Z");
                    kres.NacteniMistnosti(mistnost);
                    kres.PsaniStat(zdravi, bonus, items, zlato);
                    kres.RozmisteniPredmetu(15);
                    kres.PsaniEnemy(orc.name , orc.description);
                    kres.VykresleniThread(kres);
                }
            }
            else if (GetAsyncKeyState(VK_UP)) {
                bool testD = false;
                for (int i = 0; i < mistnost.dvere.size(); i++) {
                    if (mistnost.dvere[i]=="D_S") {
                        testD = true;
                    }
                }
                if (testD) {
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_J");
                    kres.NacteniMistnosti(mistnost);
                    kres.PsaniStat(zdravi, bonus, items, zlato);
                    kres.RozmisteniPredmetu(20);
                    kres.PsaniEnemy(orc.name , orc.description);
                    kres.VykresleniThread(kres);
                }
            }
            else if (GetAsyncKeyState(VK_DOWN)) {
                bool testD = false;
                for (int i = 0; i < mistnost.dvere.size(); i++) {
                    if (mistnost.dvere[i]=="D_J") {
                        testD = true;
                    }
                }
                if (testD) {
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_S");
                    kres.NacteniMistnosti(mistnost);
                    kres.PsaniStat(zdravi, bonus, items, zlato);
                    kres.RozmisteniPredmetu(5);
                    kres.PsaniEnemy(orc.name , orc.description);
                    kres.VykresleniThread(kres);
                }
            }
        }
//
//     delete columns;
//     delete rows;
//     return 0;
// }
