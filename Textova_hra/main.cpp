#include <iostream>
#include <random>
#include <vector>
#include "src/dice_roll.h"
#include "src/enemy_types.h"
#include "src/inventory.h"
#include "src/combat.h"
#include "src/StatBar.h"
#include "src/Kresleni.h"
#include "src/pravidla_hry.h"
#include "src/Mistnost.h"
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>

int main() {
    // Inicializace
    Combat::enemy_damage = 0;
     std::cout << "\n========================================\n";
    std::cout << "       DUNGEON CRAWLER - HRA            \n";
    std::cout << "========================================\n\n";

    showMenu();

    // Inicializuj loot systém
    initLootSystem("loot_table.txt");

    // Vytvoř hráče
    StatBar playerStats(100, 0);  // 100 HP, 0 gold
    Combat combat(playerStats);



    std::cout << "Zacatecni stav hrace:\n";
    playerStats.display();

    // std::cout << "\nStiskni Enter pro start...\n";
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // ============================================
    // HLAVNÍ HRA S KRESLENÍM
    // ============================================
    try {
        int* columns = new int;
        int* rows = new int;

        srand(time(0));

        // Získej rozměry console
        Kresleni::ZiskaniVelikostiConsole(*columns, *rows);

        // Ochrana proti neplatným rozměrům
        if (*columns <= 0) *columns = 80;
        if (*rows <= 0) *rows = 30;

        // std::cout << "[INFO] Pouzivam rozmery: " << *columns << "x" << *rows << "\n";

        Kresleni kres(*columns - 1, *rows - 1);

        // Vytvoř počáteční místnost
        Enemy currentEnemy = getRandomEnemy(1);
        Mistnost mistnost(true);
        mistnost.VyberMistnost();

        kres.NacteniMistnosti(mistnost);
        kres.PsaniStat(
            std::to_string(playerStats.getHealth()),
            std::to_string(playerStats.getCombatBonus()),
            playerStats.getInventory(),
            std::to_string(playerStats.getGold())
        );
        kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "");

        std::cout << "\n[INFO] Hra spustena! Pouzivej sipky pro pohyb mezi mistnostmi.\n";
        std::cout << "[INFO] Stiksni ESC pro ukonceni.\n\n";

        // Počáteční vykreslení
        kres.Vykresleni(kres);

        // Hlavní herní smyčka
        auto lastRender = std::chrono::steady_clock::now();
        while (true) {
            // Vykresluj každých 50ms
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRender).count() >= 50) {
                kres.Vykresleni(kres);
                lastRender = now;
            }
            // Kontrola ESC pro ukončení
            if (GetAsyncKeyState(VK_ESCAPE)) {
                std::cout << "\n[INFO] Ukoncuji hru...\n";
                break;
            }

            // Kontrola, jestli hráč žije
            if (!playerStats.isAlive()) {
                std::cout << "\n\n*** GAME OVER - ZEMREL JSI! ***\n";
                std::cout << "Stiskni ESC pro ukonceni...\n";
                while (!GetAsyncKeyState(VK_ESCAPE)) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                break;
            }

            // POHYB VLEVO (←)
            if (GetAsyncKeyState(VK_LEFT)) {
                bool maDvere = false;
                for (const auto& d : mistnost.dvere) {
                    if (d == "D_Z") maDvere = true;
                }

                if (maDvere) {
                    // Náhodná šance na nepřítele
                    bool tvorbaNepritele = (rand() % 10) <= 7;
                    bool victory = true;

                    if (tvorbaNepritele) {
                        currentEnemy = getRandomEnemy(rand() % 4 + 1);
                        victory = combat.fight(currentEnemy);
                        if (tvorbaNepritele) {
                            currentEnemy = getRandomEnemy(rand() % 4 + 1);
                            victory = combat.fight(currentEnemy);

                            kres.NastavVysledkyBoje(
                                Combat::last_player_roll,
                                Combat::last_player_bonus,
                                Combat::last_player_total,
                                Combat::last_enemy_roll,
                                Combat::last_enemy_bonus,
                                Combat::last_enemy_total,
                                Combat::last_battle_won
                            );
                        }
                    }

                    kres.Vymaz();
                    mistnost.VyberMistnost("D_V");
                    kres.NacteniMistnosti(mistnost);
                    kres.RozmisteniPredmetu(15);

                    if (tvorbaNepritele) {
                        if (victory) {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Vyhral jsi!");
                        } else {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description,
                                "Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage");
                        }
                    } else {
                        kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Mistnost je prazdna!");
                    }

                    kres.PsaniStat(
                        std::to_string(playerStats.getHealth()),
                        std::to_string(playerStats.getCombatBonus()),
                        playerStats.getInventory(),
                        std::to_string(playerStats.getGold())
                    );
                    kres.RozmisteniPredmetu(10);

                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
            }

            // POHYB VPRAVO (→)
            else if (GetAsyncKeyState(VK_RIGHT)) {
                bool maDvere = false;
                for (const auto& d : mistnost.dvere) {
                    if (d == "D_V") maDvere = true;
                }

                if (maDvere) {
                    bool tvorbaNepritele = (rand() % 10) <= 7;
                    bool victory = true;

                    if (tvorbaNepritele) {
                        currentEnemy = getRandomEnemy(rand() % 4 + 1);
                        victory = combat.fight(currentEnemy);
                        if (tvorbaNepritele) {
                            currentEnemy = getRandomEnemy(rand() % 4 + 1);
                            victory = combat.fight(currentEnemy);

                            kres.NastavVysledkyBoje(
                                Combat::last_player_roll,
                                Combat::last_player_bonus,
                                Combat::last_player_total,
                                Combat::last_enemy_roll,
                                Combat::last_enemy_bonus,
                                Combat::last_enemy_total,
                                Combat::last_battle_won
                            );
                        }
                    }

                    kres.Vymaz();
                    mistnost.VyberMistnost("D_Z");
                    kres.NacteniMistnosti(mistnost);
                    kres.RozmisteniPredmetu(15);

                    if (tvorbaNepritele) {
                        if (victory) {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Vyhral jsi!");
                        } else {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description,
                                "Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage");
                        }
                    } else {
                        kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Mistnost je prazdna!");
                    }

                    kres.PsaniStat(
                        std::to_string(playerStats.getHealth()),
                        std::to_string(playerStats.getCombatBonus()),
                        playerStats.getInventory(),
                        std::to_string(playerStats.getGold())
                    );

                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
            }

            // POHYB NAHORU (↑)
            else if (GetAsyncKeyState(VK_UP)) {
                bool maDvere = false;
                for (const auto& d : mistnost.dvere) {
                    if (d == "D_S") maDvere = true;
                }

                if (maDvere) {
                    bool tvorbaNepritele = (rand() % 10) <= 7;
                    bool victory = true;

                    if (tvorbaNepritele) {
                        currentEnemy = getRandomEnemy(rand() % 4 + 1);
                        victory = combat.fight(currentEnemy);
                        if (tvorbaNepritele) {
                            currentEnemy = getRandomEnemy(rand() % 4 + 1);
                            victory = combat.fight(currentEnemy);

                            kres.NastavVysledkyBoje(
                                Combat::last_player_roll,
                                Combat::last_player_bonus,
                                Combat::last_player_total,
                                Combat::last_enemy_roll,
                                Combat::last_enemy_bonus,
                                Combat::last_enemy_total,
                                Combat::last_battle_won
                            );
                        }
                    }

                    kres.Vymaz();
                    mistnost.VyberMistnost("D_J");
                    kres.NacteniMistnosti(mistnost);
                    kres.RozmisteniPredmetu(15);

                    if (tvorbaNepritele) {
                        if (victory) {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Vyhral jsi!");
                        } else {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description,
                                "Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage");
                        }
                    } else {
                        kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Mistnost je prazdna!");
                    }

                    kres.PsaniStat(
                        std::to_string(playerStats.getHealth()),
                        std::to_string(playerStats.getCombatBonus()),
                        playerStats.getInventory(),
                        std::to_string(playerStats.getGold())
                    );

                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
            }

            // POHYB DOLŮ (↓)
            else if (GetAsyncKeyState(VK_DOWN)) {
                bool maDvere = false;
                for (const auto& d : mistnost.dvere) {
                    if (d == "D_J") maDvere = true;
                }

                if (maDvere) {
                    bool tvorbaNepritele = (rand() % 10) <= 7;
                    bool victory = true;

                    if (tvorbaNepritele) {
                        currentEnemy = getRandomEnemy(rand() % 4 + 1);
                        victory = combat.fight(currentEnemy);
                        if (tvorbaNepritele) {
                            currentEnemy = getRandomEnemy(rand() % 4 + 1);
                            victory = combat.fight(currentEnemy);

                            kres.NastavVysledkyBoje(
                                Combat::last_player_roll,
                                Combat::last_player_bonus,
                                Combat::last_player_total,
                                Combat::last_enemy_roll,
                                Combat::last_enemy_bonus,
                                Combat::last_enemy_total,
                                Combat::last_battle_won
                            );
                        }
                        if (tvorbaNepritele) {
                            currentEnemy = getRandomEnemy(rand() % 4 + 1);
                            victory = combat.fight(currentEnemy);
                            if (tvorbaNepritele) {
                                currentEnemy = getRandomEnemy(rand() % 4 + 1);
                                victory = combat.fight(currentEnemy);

                                kres.NastavVysledkyBoje(
                                    Combat::last_player_roll,
                                    Combat::last_player_bonus,
                                    Combat::last_player_total,
                                    Combat::last_enemy_roll,
                                    Combat::last_enemy_bonus,
                                    Combat::last_enemy_total,
                                    Combat::last_battle_won
                                );
                            }

                            kres.NastavVysledkyBoje(
                                Combat::last_player_roll,
                                Combat::last_player_bonus,
                                Combat::last_player_total,
                                Combat::last_enemy_roll,
                                Combat::last_enemy_bonus,
                                Combat::last_enemy_total,
                                Combat::last_battle_won
                            );
                        }
                    }

                    kres.Vymaz();
                    mistnost.VyberMistnost("D_S");
                    kres.NacteniMistnosti(mistnost);
                    kres.RozmisteniPredmetu(15);

                    if (tvorbaNepritele) {
                        if (victory) {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Vyhral jsi!");
                        } else {
                            kres.PsaniEnemy(currentEnemy.name, currentEnemy.description,
                                "Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage");
                        }
                    } else {
                        kres.PsaniEnemy(currentEnemy.name, currentEnemy.description, "Mistnost je prazdna!");
                    }

                    kres.PsaniStat(
                        std::to_string(playerStats.getHealth()),
                        std::to_string(playerStats.getCombatBonus()),
                        playerStats.getInventory(),
                        std::to_string(playerStats.getGold())
                    );

                    std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
            }

            // Malá pauza aby nedošlo k přetížení CPU
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        delete columns;
        delete rows;

    } catch (const std::exception& e) {
        std::cerr << "\n[KRITICKA CHYBA] " << e.what() << "\n";
        return 1;
    }

    std::cout << "\n========================================\n";
    std::cout << "         FINALNI STATISTIKY             \n";
    std::cout << "========================================\n";
    playerStats.display();

    std::cout << "\n========================================\n";
    std::cout << "    DEKUJEME ZA HRU!                     \n";
    std::cout << "========================================\n";

    return 0;
}