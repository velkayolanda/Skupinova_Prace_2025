//
// Created by Jar Jar Banton on 7. 11. 2025. made by sevci
//

#include "pravidla_hry.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

void slowPrint(const std::string& text, int delayMs) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}

void printIntro() {
    slowPrint(
            "V hlubinach pod zborenou pevnosti Karak lezi labyrint,\n"
            "ktery se meni jako zivy organismus. Chodby se preskupují,\n"
            "mistnosti dychaji tichou temnotou a kazdy krok muze byt posledni.\n\n"

            "Rika se, ze v samotnem srdci podzemi spi draci tyran Mor'Karath,\n"
            "postrach starych kralovstvi, bytost tak mocna, ze i stiny pred nim\n"
            "uhybaji. Jeho dech spaluje duse a jeho srdce je poklad,\n"
            "ktery dokaze změnit osud toho, kdo jej ziska.\n\n"

            "Mnozi se pokusili projít temnim bludištěm Karaku...\n"
            "mnozi se ztratili, mnozi zemřeli, ale nikdo se nevratil s dracim pokladem.\n\n"

            "Ted prichazis ty.\n"
            "Vybaven jen odvahu, slabou zbrani a nadeji,\n"
            "ze temnota ustoupi pred tvym odhodlanim.\n\n"

            "Vstup do Karaku.\n"
            "Kazdy tvuj krok se zapise do kronik... nebo do zapomenuti.\n\n"
    );
}



void printRules(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Nelze otevrit soubor s pravidly: " << filename << endl;
        return;
    }

    cout << "\n===== PRAVIDLA HRY =====\n\n";

    string line;
    while (getline(file, line)) {
        slowPrint(line + "\n", 5);
    }

    cout << "\n=========================\n";
}


void showMenu() {
    while (true) {
        cout << "===== HLAVNI MENU =====\n";
        cout << "1. Zacit hru\n";
        cout << "2. Vypsat pravidla\n";
        cout << "3. Ukoncit\n";
        cout << "Volba: ";

        int volba;
        cin >> volba;

        if (volba == 1) {
            printIntro();
            slowPrint("Hra zacala...\n\n", 20);
            break;
        }
        else if (volba == 2) {
            printRules("pravidla.txt");
        }
        else if (volba == 3) {
            slowPrint("Ukoncuji hru...\n", 20);
            exit(0);
        }
        else {
            cout << "Neplatna volba.\n";
        }
    }
}


