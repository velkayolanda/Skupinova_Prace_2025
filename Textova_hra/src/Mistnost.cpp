#include "Mistnost.h"
#include "fstream"
#include <sstream>



Mistnost::Mistnost(bool prvni): prvni(prvni) {
    std::ifstream cteni("1J_Ctverec.txt");
    std::string radek;
    char CHdalsiM = ';';
    std::string SZacatekM;
    std::string SKonecM;
    std::string NazevM;


    if (cteni.is_open()) {
        while(getline(cteni, radek)) {
            std::stringstream ss(radek);
            std::string token;
            while (getline(ss, token, CHdalsiM)) {
                if (token == "D") {
                    std::getline(ss, SZacatekM, CHdalsiM);
                    std::getline(ss, SKonecM, CHdalsiM);
                    std::getline(ss, NazevM);
                    txtmistnost.insert({NazevM,{ std::stoi(SZacatekM), std::stoi(SKonecM) }});
                    stxtmistnost.push_back(NazevM);
                }
            }
        }
        }
    cteni.close();
    }

std::string Mistnost::NacteniMistnosti(std::string PozadovanaM) {
    std::ifstream cteni("1J_Ctverec.txt");
    std::string radek;
    char CHdalsiZnak = ';';
    cary.clear();

    if (cteni.is_open()) {
        for (int j = 1; j <= txtmistnost[PozadovanaM].EndM; j++) {
            std::getline(cteni,radek);
            if (txtmistnost[PozadovanaM].StartM <= j) {
                std::stringstream ss(radek);
                std::string token;
                std::string pozicex;
                std::string pozicey;
                std::string x1;
                std::string x2;
                std::string y1;
                std::string y2;
                while (getline(ss, token, CHdalsiZnak)) {
                    if (token == "D_J" || token == "D_S" || token == "D_Z" || token == "D_V") {
                        dvere = token;
                    }
                    if (token =="C") {
                        std::getline(ss, pozicex, CHdalsiZnak);
                        std::getline(ss, pozicey, CHdalsiZnak);
                        std::stringstream ssx(pozicex);
                        std::stringstream ssy(pozicey);
                        std::getline(ssx, x1, ',');
                        std::getline(ssx, x2);
                        std::getline(ssy, y1, ',');
                        std::getline(ssy, y2);
                        cary.push_back({std::stoi(x1),std::stoi(x2),std::stoi(y1),std::stoi(y2)});
                    }
                }
            }

            }
        }
    cteni.close();
    return dvere;
}

void Mistnost::VyberMistnost(std::string PozadovaneD) {
    std::string radek;
    std::srand(time(0));
        std::string mdvere;
        while (mdvere != PozadovaneD) {
            int vyber = std::rand() % txtmistnost.size();
            mdvere =  NacteniMistnosti(stxtmistnost[vyber]);
        }

}

void Mistnost::VyberMistnost() {
    std::string radek;
    std::srand(time(0));
    int vyber = std::rand() % txtmistnost.size();
    if (prvni) {
        NacteniMistnosti(stxtmistnost[vyber]);
    }
}
