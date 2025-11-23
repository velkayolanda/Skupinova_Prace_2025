#include "Mistnost.h"
#include <fstream>
#include <sstream>
#include <iostream>

Mistnost::Mistnost(bool prvni): prvni(prvni) {
    // DŮLEŽITÉ: Stejná cesta jako v NacteniMistnosti()!
    std::string cesta = "data/1J_Ctverec.txt";
    std::ifstream cteni(cesta);
    std::string radek;
    char CHdalsiM = ';';
    std::string SZacatekM;
    std::string SKonecM;
    std::string NazevM;

    std::cout << "[DEBUG Mistnost] Konstruktor: oteviram soubor " << cesta << "\n";

    if (!cteni.is_open()) {
        std::cerr << "[CHYBA Mistnost] Nelze otevrit soubor: " << cesta << "\n";
        std::cerr << "[INFO Mistnost] Zkontrolujte, ze soubor existuje v teto ceste!\n";
        return;
    }

    std::cout << "[DEBUG Mistnost] Soubor uspesne otevren, nacitam definice...\n";

    int lineNum = 0;
    while(getline(cteni, radek)) {
        lineNum++;
        std::stringstream ss(radek);
        std::string token;
        while (getline(ss, token, CHdalsiM)) {
            if (token == "D") {
                std::getline(ss, SZacatekM, CHdalsiM);
                std::getline(ss, SKonecM, CHdalsiM);
                std::getline(ss, NazevM);
                txtmistnost.insert({NazevM,{ std::stoi(SZacatekM), std::stoi(SKonecM) }});
                stxtmistnost.push_back(NazevM);
                std::cout << "[DEBUG Mistnost] Radek " << lineNum << ": Nactena mistnost '"
                          << NazevM << "' (radky " << SZacatekM << "-" << SKonecM << ")\n";
            }
        }
    }
    cteni.close();
    std::cout << "[DEBUG Mistnost] Konstruktor: celkem nacteno " << stxtmistnost.size() << " mistnosti\n";
}

std::string Mistnost::NacteniMistnosti(std::string PozadovanaM) {
    // DŮLEŽITÉ: Stejná cesta jako v konstruktoru!
    std::string cesta = "data/1J_Ctverec.txt";
    std::ifstream cteni(cesta);
    std::string radek;
    char CHdalsiZnak = ';';
    cary.clear();

    std::cout << "[DEBUG Mistnost] NacteniMistnosti: oteviram soubor " << cesta << "\n";

    if (!cteni.is_open()) {
        std::cerr << "[CHYBA Mistnost] Nelze otevrit soubor: " << cesta << "\n";
        return "";
    }

    std::cout << "[DEBUG Mistnost] Nacitam mistnost: '" << PozadovanaM << "'\n";

    // Kontrola, jestli místnost existuje
    if (txtmistnost.find(PozadovanaM) == txtmistnost.end()) {
        std::cerr << "[CHYBA Mistnost] Mistnost '" << PozadovanaM << "' nenalezena v tabulce!\n";
        std::cerr << "[INFO Mistnost] Dostupne mistnosti: ";
        for (const auto& m : stxtmistnost) {
            std::cerr << "'" << m << "' ";
        }
        std::cerr << "\n";
        return "";
    }

    int startLine = txtmistnost[PozadovanaM].StartM;
    int endLine = txtmistnost[PozadovanaM].EndM;
    std::cout << "[DEBUG Mistnost] Ctu radky " << startLine << "-" << endLine << "\n";

    for (int j = 1; j <= endLine; j++) {
        if (!std::getline(cteni, radek)) {
            std::cerr << "[CHYBA Mistnost] Nedostatek radku v souboru (dosahli jsme konce na radku " << j << ")\n";
            break;
        }

        if (startLine <= j && j <= endLine) {
            std::cout << "[DEBUG Mistnost] Radek " << j << ": '" << radek << "'\n";

            std::stringstream ss(radek);
            std::string token;
            std::string pozicex;
            std::string pozicey;
            std::string x1, x2, y1, y2;

            while (getline(ss, token, CHdalsiZnak)) {
                if (token == "D_J" || token == "D_S" || token == "D_Z" || token == "D_V") {
                    dvere = token;
                    std::cout << "[DEBUG Mistnost] Nalezeny dvere: '" << dvere << "'\n";
                }
                if (token == "C") {
                    std::getline(ss, pozicex, CHdalsiZnak);
                    std::getline(ss, pozicey, CHdalsiZnak);

                    std::cout << "[DEBUG Mistnost] Parsuju caru: x='" << pozicex
                              << "', y='" << pozicey << "'\n";

                    std::stringstream ssx(pozicex);
                    std::stringstream ssy(pozicey);
                    std::getline(ssx, x1, ',');
                    std::getline(ssx, x2);
                    std::getline(ssy, y1, ',');
                    std::getline(ssy, y2);

                    try {
                        int ix1 = std::stoi(x1);
                        int ix2 = std::stoi(x2);
                        int iy1 = std::stoi(y1);
                        int iy2 = std::stoi(y2);

                        cary.push_back({ix1, ix2, iy1, iy2});
                        std::cout << "[DEBUG Mistnost] Pridana cara: (" << ix1 << "," << iy1
                                  << ") -> (" << ix2 << "," << iy2 << ")\n";
                    }
                    catch (const std::exception& e) {
                        std::cerr << "[CHYBA Mistnost] Nelze parsovat souradnice: " << e.what() << "\n";
                        std::cerr << "[INFO Mistnost] x1='" << x1 << "' x2='" << x2
                                  << "' y1='" << y1 << "' y2='" << y2 << "'\n";
                    }
                }
            }
        }
    }

    cteni.close();
    std::cout << "[DEBUG Mistnost] NacteniMistnosti dokonceno: " << cary.size() << " car\n";
    return dvere;
}

void Mistnost::VyberMistnost(std::string PozadovaneD) {
    std::srand(static_cast<unsigned>(time(0)));
    std::string mdvere;
    int pokus = 0;

    std::cout << "[DEBUG Mistnost] VyberMistnost: hledam mistnost s dvermi '" << PozadovaneD << "'\n";

    while (mdvere != PozadovaneD && pokus < 100) {
        if (txtmistnost.empty()) {
            std::cerr << "[CHYBA Mistnost] Tabulka mistnosti je prazdna!\n";
            return;
        }
        int vyber = std::rand() % txtmistnost.size();
        mdvere = NacteniMistnosti(stxtmistnost[vyber]);
        pokus++;
    }

    if (pokus >= 100) {
        std::cerr << "[CHYBA Mistnost] Nenalezena mistnost s dvermi '" << PozadovaneD
                  << "' po 100 pokusech\n";
    }
}

void Mistnost::VyberMistnost() {
    std::srand(static_cast<unsigned>(time(0)));

    std::cout << "[DEBUG Mistnost] VyberMistnost: nahodny vyber z " << stxtmistnost.size() << " mistnosti\n";

    if (stxtmistnost.empty()) {
        std::cerr << "[CHYBA Mistnost] Zadne mistnosti k vyber!\n";
        return;
    }

    int vyber = std::rand() % stxtmistnost.size();
    std::cout << "[DEBUG Mistnost] Vybrana mistnost cislo " << vyber
              << " ('" << stxtmistnost[vyber] << "')\n";

    if (prvni) {
        NacteniMistnosti(stxtmistnost[vyber]);
    }
}