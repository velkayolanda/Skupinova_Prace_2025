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
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>


// Helper funkce pro cekani na Enter
void waitForEnter() {
    std::cout << "\nStlac Enter pre pokracovanie...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Combat::enemy_damage = 0;
    showMenu();
    // ============================================
    // 0. TEST: KOCKA
    // ============================================
    std::cout << "=== TEST KOCKY ===\n";
    std::cout << "Hadzenie d20 (5x):\n";
    for (int i = 1; i <= 5; i++) {
        int roll = rollDice(20);
        std::cout << "Hod " << i << ": " << roll << "\n";
    }

    std::cout << "\nHadzenie 3d20:\n";
    int multiRoll = rollMultipleDice(3, 20);
    std::cout << "Sucet: " << multiRoll << "\n\n";

    waitForEnter();

    // ============================================
    // 1. INICIALIZACE LOOT SYSTEMU
    // ============================================
    initLootSystem("data/loot_table.txt");

    std::cout << "\n=== LOOT SYSTEM TEST ===\n\n";

    // 2a. TEST: Pouziti v mistnosti
    std::cout << "--- Vstupil si do miestnosti ---\n";
    if (rollForLoot(70)) {  // 70% sanca na loot
        Item loot = getRandomLootGlobal();
        std::cout << "Nasiel si: " << loot.name << " (+" << loot.combatBonus
                  << " combat, " << loot.value << " gold)\n";
    } else {
        std::cout << "Miestnost je prazdna.\n";
    }

    // 2b. TEST: Loot podla typu
    std::cout << "\n--- Otvoril si zbrojnu truhlu ---\n";
    Item weapon = getRandomLootByTypeGlobal("weapon");
    std::cout << "Ziskal si zbran: " << weapon.name << "\n";

    // 2c. TEST: Loot podla hodnoty
    std::cout << "\n--- Mala pokladnicka ---\n";
    Item cheapLoot = getRandomLootByValueGlobal(5, 25);
    std::cout << "Nasiel si: " << cheapLoot.name << "\n";

    // 2d. TEST: Velka miestnost
    std::cout << "\n--- Dracia pokladnica ---\n";
    Item expensiveLoot = getRandomLootByValueGlobal(50, 100);
    std::cout << "Ziskal si: " << expensiveLoot.name << "\n";

    // 3. TEST: Simulace 5 mistnosti
    std::cout << "\n\n=== SIMULACIA 5 MIESTNOSTI ===\n";
    for (int room = 1; room <= 5; room++) {
        std::cout << "\nMiestnost " << room << ": ";

        if (rollForLoot(50)) {
            if (room <= 2) {
                Item item = getRandomLootByValueGlobal(0, 20);
                std::cout << "Nasiel si " << item.name;
            } else if (room <= 4) {
                Item item = getRandomLootByValueGlobal(15, 50);
                std::cout << "Nasiel si " << item.name;
            } else {
                Item item = getRandomLootByValueGlobal(50, 100);
                std::cout << "Nasiel si " << item.name << " !!!";
            }
        } else {
            std::cout << "Prazdna";
        }
    }

    std::cout << "\n\n=== LOOT SYSTEM FUNKCNY! ===\n";
    waitForEnter();

    // ============================================
    // 5. TEST: COMBAT SYSTEM S STATBAR
    // ============================================
    std::cout << "\n\n========================================\n";
    std::cout << "       TEST BOJOVEHO SYSTEMU            \n";
    std::cout << "========================================\n\n";

    // Inicializuj hrace pomoci StatBar
    StatBar playerStats(100, 50);  // 100 HP, 50 gold

    std::cout << "Zaciatocny stav hraca:\n";
    playerStats.display();

    // Vytvor bojovy system
    Combat combat(playerStats);

    std::cout << "\nZakladny test - bez vybavenia\n";
    waitForEnter();

    // Test 1: Tier 1 nepriatel
    std::cout << "\n--- TEST 1: Tier 1 nepriatel ---\n";
    std::cout << "[DEBUG] Ziskavam nepriatela tier 1...\n";
    Enemy rat = getRandomEnemy(1);
    std::cout << "[DEBUG] Nepriatel: " << rat.name << "\n";
    std::cout << "[DEBUG] Zacinam boj...\n";
    bool victory1 = combat.fight(rat);
    std::cout << "[DEBUG] Boj skoncil\n";

    if (victory1) {
        std::cout << "\n";
        playerStats.display();
    }
    waitForEnter();

    // Test 2: Tier 2 nepriatel
    if (playerStats.isAlive()) {
        std::cout << "\n--- TEST 2: Tier 2 nepriatel ---\n";
        Enemy orc = getRandomEnemy(2);
        bool victory2 = combat.fight(orc);

        if (victory2) {
            std::cout << "\n";
            playerStats.display();
        }
        waitForEnter();
    }

    // Test 3: Tier 3 nepriatel
    if (playerStats.isAlive()) {
        std::cout << "\n--- TEST 3: Tier 3 nepriatel ---\n";
        Enemy troll = getRandomEnemy(3);
        bool victory3 = combat.fight(troll);

        if (victory3) {
            std::cout << "\n";
            playerStats.display();
        }
        waitForEnter();
    }

    // Test 4: Boss
    if (playerStats.isAlive() && playerStats.getInventory().size() >= 2) {
        std::cout << "\n--- TEST 4: BOSS FIGHT (Tier 4) ---\n";
        Enemy boss = getRandomEnemy(4);
        bool victory4 = combat.fight(boss);

        if (victory4) {
            std::cout << "\n*** GRATULUJEM! Porazil si bossa! ***\n";
            playerStats.display();
        }
        waitForEnter();
    }

    // Finalni statistiky
    std::cout << "\n========================================\n";
    std::cout << "         FINALNE STATISTIKY             \n";
    std::cout << "========================================\n";
    playerStats.display();

    if (!playerStats.isAlive()) {
        std::cout << "\n*** ZOMREL SI V DUNGEONE ***\n";
    }

    std::cout << "\n=== COMBAT SYSTEM FUNKCNY! ===\n";
    waitForEnter();

    // ============================================
    // 6. TEST: INVENTORY SYSTEM
    // ============================================
    std::cout << "\n\n========================================\n";
    std::cout << "       TEST INVENTARA                   \n";
    std::cout << "========================================\n\n";

    // Inventar: 5 zbrani, 3 lektvary, 3 brneni, 2 sloty
    inventory inv(5, 3, 3, 2);

    std::cout << "--- TEST 1: Pridavanie predmetov ---\n";

    // Predmety
    inventory::InventoryItem mec("Hrdzavy mec", inventory::ItemType::Weapon, 1);
    inventory::InventoryItem luk("Dlhy luk", inventory::ItemType::Weapon, 1);
    inventory::InventoryItem stit("Dreveny stit", inventory::ItemType::Armor, 1);
    inventory::InventoryItem lektvar("Lektvar zdravia", inventory::ItemType::Potion, 2);
    inventory::InventoryItem kluc("Stary kluc", inventory::ItemType::Misc, 1);

    inv.addItem(mec);
    inv.addItem(luk);
    inv.addItem(stit);
    inv.addItem(lektvar);
    inv.addItem(kluc);
    inv.addGold(100);

    std::cout << "Pridane: Mec, Luk, Stit, 2x Lektvar, Kluc, 100 zlata\n\n";
    inv.display();
    waitForEnter();

    // TEST 2: Equip
    std::cout << "\n--- TEST 2: Vybavenie predmetov ---\n";
    std::cout << "Vybavujem mec do slotu 0...\n";
    if (inv.equipItem("Hrdzavy mec", 0)) {
        std::cout << "Uspesne vybaveny!\n";
    }

    std::cout << "Vybavujem stit do slotu 1...\n";
    if (inv.equipItem("Dreveny stit", 1)) {
        std::cout << "Uspesne vybaveny!\n";
    }

    std::cout << "\n";
    inv.display();
    waitForEnter();

    // TEST 3: Pouzitie lektvaru
    std::cout << "\n--- TEST 3: Pouzitie lektvaru ---\n";
    std::cout << "Pouzivam 1x Lektvar zdravia...\n";
    if (inv.removeItem("Lektvar zdravia", 1)) {
        std::cout << "Lektvar pouzity! +50 HP\n";
    }

    std::cout << "\n";
    inv.display();
    waitForEnter();

    // TEST 4: Loot
    std::cout << "\n--- TEST 4: Ziskavanie lootu ---\n";
    std::cout << "Porazil si nepriatelov a ziskal si:\n";

    Item loot1 = getRandomLootByTypeGlobal("weapon");
    Item loot2 = getRandomLootByValueGlobal(10, 30);

    std::cout << "- " << loot1.name << " (typ: " << loot1.type << ")\n";
    std::cout << "- " << loot2.name << " (typ: " << loot2.type << ")\n";

    if (inv.addLoot(loot1)) {
        std::cout << loot1.name << " pridany do inventara!\n";
    } else {
        std::cout << loot1.name << " - inventar plny!\n";
    }

    if (inv.addLoot(loot2)) {
        std::cout << loot2.name << " pridany do inventara!\n";
    } else {
        std::cout << loot2.name << " - inventar plny!\n";
    }

    inv.addGold(50);
    std::cout << "Ziskane zlato: +50\n\n";
    inv.display();
    waitForEnter();

    // TEST 5: Nakupovanie
    std::cout << "\n--- TEST 5: Nakupovanie v obchode ---\n";
    std::cout << "Kupujes novy lektvar za 30 zlata...\n";

    if (inv.spendGold(30)) {
        std::cout << "Kupene!\n";
        inventory::InventoryItem novyLektvar("Velky lektvar", inventory::ItemType::Potion, 1);
        inv.addItem(novyLektvar);
    } else {
        std::cout << "Nemas dost zlata!\n";
    }

    std::cout << "\n";
    inv.display();
    waitForEnter();

    // TEST 6: Odvybavenie
    std::cout << "\n--- TEST 6: Odvybavenie predmetu ---\n";
    std::cout << "Odvybavujem mec zo slotu 0...\n";

    if (inv.unequip(0)) {
        std::cout << "Uspesne odvybaveny!\n";
    }

    std::cout << "\n";
    inv.display();
    waitForEnter();

    // TEST 7: Plny inventar
    std::cout << "\n--- TEST 7: Test plneho inventara ---\n";
    std::cout << "Pokusam sa pridavat zbrane az do zaplnenia...\n";

    int pokusyZbrane = 0;
    while (pokusyZbrane < 10) {
        inventory::InventoryItem novaZbran("Zbran " + std::to_string(pokusyZbrane),
                                  inventory::ItemType::Weapon, 1);
        if (!inv.addItem(novaZbran)) {
            std::cout << "Inventar zbrani je plny po " << pokusyZbrane << " pokusoch!\n";
            break;
        }
        pokusyZbrane++;
    }

    std::cout << "\n";
    inv.display();

    std::cout << "\n========================================\n";
    std::cout << "       FINALNY STAV INVENTARA           \n";
    std::cout << "========================================\n";
    std::cout << "Celkove zlato: " << inv.getGold() << "\n";
    std::cout << "\n=== INVENTORY SYSTEM FUNKCNY! ===\n";

    waitForEnter();

    // ============================================
    // 7. TEST: KRESLENI (volitelne)
    // ============================================
    std::cout << "\n========================================\n";
    std::cout << "       TEST KRESLENIA (nepovinne)       \n";
    std::cout << "========================================\n";
    std::cout << "Chces spustit test kreslenia? (y/n): ";

    char odpoved;
    std::cin >> odpoved;
    std::cin.ignore(); // Vycisti buffer

    if (odpoved == 'y' || odpoved == 'Y') {
        int columns = 80;
        int rows = 24;

        try {
     int* columns, *rows;
        columns = new int;
        rows = new int;
        srand(time(0));
        Kresleni::ZiskaniVelikostiConsole(*columns, *rows);
        Kresleni kres(*columns-1,*rows-1);


        Enemy orc = getRandomEnemy(1);
        Mistnost mistnost(true);
        mistnost.VyberMistnost();
        kres.NacteniMistnosti(mistnost);
        kres.PsaniStat(std::to_string(playerStats.getHealth()), std::to_string(playerStats.getCombatBonus()), playerStats.getInventory(), std::to_string(playerStats.getGold()));
        kres.PsaniEnemy(orc.name, orc.description,"");
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
                    bool victory;
                    bool tvorbaN = false;
                    int nahodatvorban = rand()%10;
                    if (nahodatvorban>7) {
                        tvorbaN = false;
                    }
                    else {
                        tvorbaN = true;
                    }
                    if (tvorbaN) {
                        orc = getRandomEnemy(rand()%4);
                        victory = combat.fight(orc);
                    }
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_V");
                    kres.NacteniMistnosti(mistnost);
                    if (tvorbaN) {
                        if (victory) {
                            kres.PsaniEnemy(orc.name , orc.description, "Vyhral jsi!");
                        }
                        else {
                            kres.PsaniEnemy(orc.name , orc.description,("Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage"));
                        }
                    }
                    else {
                        kres.PsaniEnemy(orc.name , orc.description, "Mistnost je prazdna!");
                    }
                    kres.PsaniStat(std::to_string(playerStats.getHealth()), std::to_string(playerStats.getCombatBonus()), playerStats.getInventory(), std::to_string(playerStats.getGold()));                    kres.RozmisteniPredmetu(10);
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
                    bool victory;
                    bool tvorbaN = false;
                    int nahodatvorban = rand()%10;
                    if (nahodatvorban>7) {
                        tvorbaN = false;
                    }
                    else {
                        tvorbaN = true;
                    }
                    if (tvorbaN) {
                        orc = getRandomEnemy(rand()%4);
                        victory = combat.fight(orc);
                    }
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_Z");
                    kres.NacteniMistnosti(mistnost);
                    if (tvorbaN) {
                        if (victory) {
                            kres.PsaniEnemy(orc.name , orc.description, "Vyhral jsi!");
                        }
                        else {
                            kres.PsaniEnemy(orc.name , orc.description,("Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage"));
                        }
                    }
                    else {
                        kres.PsaniEnemy(orc.name , orc.description, "Mistnost je prazdna!");
                    }
                    kres.PsaniStat(std::to_string(playerStats.getHealth()), std::to_string(playerStats.getCombatBonus()), playerStats.getInventory(), std::to_string(playerStats.getGold()));
                    kres.RozmisteniPredmetu(15);
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
                    bool victory;
                    bool tvorbaN = false;
                    int nahodatvorban = rand()%10;
                    if (nahodatvorban>7) {
                        tvorbaN = false;
                    }
                    else {
                        tvorbaN = true;
                    }
                    if (tvorbaN) {
                        orc = getRandomEnemy(rand()%4);
                        victory = combat.fight(orc);
                    }
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_J");
                    kres.NacteniMistnosti(mistnost);
                    if (tvorbaN) {
                        if (victory) {
                            kres.PsaniEnemy(orc.name , orc.description, "Vyhral jsi!");
                        }
                        else {
                            kres.PsaniEnemy(orc.name , orc.description,("Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage"));
                        }
                    }
                    else {
                        kres.PsaniEnemy(orc.name , orc.description, "Mistnost je prazdna!");
                    }
                    kres.PsaniStat(std::to_string(playerStats.getHealth()), std::to_string(playerStats.getCombatBonus()), playerStats.getInventory(), std::to_string(playerStats.getGold()));
                    kres.RozmisteniPredmetu(20);
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
                    bool victory;
                    bool tvorbaN = false;
                    int nahodatvorban = rand()%10;
                    if (nahodatvorban>7) {
                        tvorbaN = false;
                    }
                    else {
                        tvorbaN = true;
                    }
                    if (tvorbaN) {
                        orc = getRandomEnemy(rand()%4);
                        victory = combat.fight(orc);
                    }
                    kres.Vymaz();
                    mistnost.VyberMistnost("D_S");
                    kres.NacteniMistnosti(mistnost);
                    if (tvorbaN) {
                        if (victory) {
                            kres.PsaniEnemy(orc.name , orc.description, "Vyhral jsi!");
                        }
                        else {
                            kres.PsaniEnemy(orc.name , orc.description,("Prohral jsi! Dostal jsi " + std::to_string(Combat::enemy_damage) + " damage"));
                        }
                    }
                    else {
                        kres.PsaniEnemy(orc.name , orc.description, "Mistnost je prazdna!");
                    }
                    kres.PsaniStat(std::to_string(playerStats.getHealth()), std::to_string(playerStats.getCombatBonus()), playerStats.getInventory(), std::to_string(playerStats.getGold()));
                    kres.RozmisteniPredmetu(5);
                    kres.VykresleniThread(kres);
                }
            }
        }
//
//     delete columns;
//     delete rows;
// }

        }
        catch (const std::exception& e) {
            std::cerr << "[CHYBA] Vynimka pri kresleni: " << e.what() << "\n";
        }
    }

    std::cout << "\n\n========================================\n";
    std::cout << "    VSETKY SYSTEMY SU FUNKCNE!         \n";
    std::cout << "========================================\n";

    return 0;
}
