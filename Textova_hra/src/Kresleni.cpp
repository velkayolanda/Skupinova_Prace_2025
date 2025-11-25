//
// Created by Lukas on 11.11.2025.
//

#include "Kresleni.h"
#include "combat.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>
#include <conio.h>
#include "windows.h"

Kresleni::Kresleni(int sirka, int vyska)
    : sirka(sirka), vyska(vyska), sirkaPZ(0)
{
   std::cout << "\033[?25l";
   std::cout << "\033[2J";

    plocha = new char*[vyska];
    for (int i = 0; i < vyska; i++) {
        plocha[i] = new char[sirka];
        for (int j = 0; j < sirka; j++) {
            plocha[i][j] = 32;
        }
    }
}

Kresleni::~Kresleni()
{

    std::cout << "\033[?25h" << std::endl;

    for (int i = 0; i < vyska; i++) {
        delete[] plocha[i];
    }
    delete[] plocha;
}

void Kresleni::Vymaz()
{
    for (int i = 0; i < vyska; i++) {
        for (int j = 0; j < sirka; j++) {
            plocha[i][j] = ' ';
        }
    }
}

void Kresleni::Bod(int x, int y, char c)
{
    if (x >= 0 && x < sirka && y >= 0 && y < vyska) {
        plocha[y][x] = c;
    }
}

void Kresleni::Cara(int x1, int y1, int x2, int y2)
{
    if (x1 == x2) {
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
            if (y == std::min(y1, y2) || y == std::max(y1, y2))
            {
                plocha[y][x1] = '+';
            }
            else {
                plocha[y][x1] = '|';
            }
        }
    } else if (y1 == y2) {
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
            if (x == std::min(x1, x2) || x == std::max(x1, x2)) {
                plocha[y1][x] = '+';
            }
            else {
                plocha[y1][x] = '-';
            }
        }
    }
}



void Kresleni::Vykresleni(const Kresleni& kresleni) {

    std::cout << "\033[H";

    for (int i = 0; i < kresleni.vyska; i++) {
        for (int j = 0; j < kresleni.sirka; j++) {
            std::cout << kresleni.plocha[i][j];
        }
        std::cout << '\n';
    }
}

void Kresleni::VykresleniThread(Kresleni& kresleni) {
        kresleni.Vykresleni(kresleni);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void Kresleni::ZiskaniVelikostiConsole(int& columns, int& rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    short scrBufferWidth = csbi.dwSize.X;
    short scrBufferHeight = csbi.dwSize.Y;

    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = rows;


    int Status = SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), newSize);
    if (Status == 0)
    {
        std::cout << "A sakra, nekde se stala chyba, zkus to znova " << GetLastError() << std::endl;
        exit(Status);
    }
}

void Kresleni::NacteniMistnosti(Mistnost& mistnost)
{
    int minX = 0, maxX = 0;
    int minY = 0, maxY = 0;

    for (auto& c : mistnost.cary) {
        minX = std::min({minX, c.x1, c.x2});
        maxX = std::max({maxX, c.x1, c.x2});
        minY = std::min({minY, c.y1, c.y2});
        maxY = std::max({maxY, c.y1, c.y2});
    }

    int width  = maxX - minX;
    int height = maxY - minY;

    float cilovas = (sirka  * 0.75f);
    float cilovav = (vyska  * 0.75f);

    this->sirkaPZ = cilovas;

    float scaleX = cilovas / width;
    float scaleY = cilovav / height;

    float scale = std::min(scaleX, scaleY);

    float cx = minX + width  / 2.0f;
    float cy = minY + height / 2.0f;


    for (auto& c : mistnost.cary) {
        c.x1 = cx + (c.x1 - cx) * scale;
        c.x2 = cx + (c.x2 - cx) * scale;
        c.y1 = cy + (c.y1 - cy) * scale;
        c.y2 = cy + (c.y2 - cy) * scale;
    }
    for (auto& c : mistnost.cary) {
        minX = std::min({minX, c.x1, c.x2});
        minY = std::min({minY, c.y1, c.y2});
    }

    int shiftX = 0;
    int shiftY = 0;

    if (minX < 0) shiftX = -minX;
    if (minY < 0) shiftY = -minY;

    if (shiftX != 0 || shiftY != 0) {
        for (auto& c : mistnost.cary) {
            c.x1 += shiftX;
            c.x2 += shiftX;
            c.y1 += shiftY;
            c.y2 += shiftY;
        }
    }

    for (auto& c : mistnost.cary) {
        Cara(c.x1, c.y1, c.x2, c.y2);
    }
    minX = 0;
    minY = 0;
    maxX = 0;
    maxY = 0;
    for (auto& c : mistnost.cary) {
        minX = std::min({minX, c.x1, c.x2});
        maxX = std::max({maxX, c.x1, c.x2});
        minY = std::min({minY, c.y1, c.y2});
        maxY = std::max({maxY, c.y1, c.y2});
    }
    this->cx = (minX + maxX) / 2;
    this->cy = (minY + maxY)/2;
    this->minX = minX;
    this->minY = minY;
    this->maxX = maxX;
    this->maxY = maxY;
}

void Kresleni::VypisText(std::string Text, int y) {
    int zacatek = sirkaPZ+2;
    for (int i = zacatek; i < zacatek+Text.size() && i<sirka; i++) {
        plocha[y][i] = Text[i-zacatek];
    }
}

void Kresleni::VypisText(std::string Text, int zacatekx, int zacateky) {
    int zacatek = zacatekx;
    bool novyR = false;
    int j;
    for (int i = zacatek; i < zacatek+Text.size() && i<sirkaPZ; i++) {
        if (i== maxX-5) {
            zacateky++;
            novyR = true;
            j=i;
        }

        if (novyR) {
            plocha[zacateky][i-j+zacatekx] = Text[i-zacatek];
        }
        else {
            plocha[zacateky][i] = Text[i-zacatek];
        }
    }
}

void Kresleni::PsaniStat(std::string Zivoty, std::string BonusD, std::vector<Item> Item, std::string penize) {
    std::vector<std::string> text = {
        "Statistika: ",
        "Mas zivotu: " + Zivoty,
        "Bonus damage: " + BonusD,
        "Penize: " + penize,
        "Inventar:"
    };

    for (int i = 0; i < Item.size(); i++) {
        text.push_back("Item: " + Item[i].name);
    }

    if (!lastPlayerRoll.empty()) {
        text.push_back(""); // prázdný řádek
        text.push_back("=== POSLEDNY BOJ ===");
        text.push_back(lastPlayerRoll);
        text.push_back(lastEnemyRoll);
        text.push_back(lastBattleResult);
    }

    for (int i = 0; i < text.size(); i++) {
        VypisText(text[i], i);
    }
}

void Kresleni::PsaniEnemy(std::string Jmeno, std::string Popis, std::string Souboj) {

    VypisText(Jmeno, minX +5, cy);
    VypisText(Popis, minX+5, cy+1);
    VypisText(Souboj, minX+5, cy+3);
}

void Kresleni::RozmisteniPredmetu(int Mnozstvi) {

    std::vector<Pozice> PredmetyP;
    srand(time(0));


    int velikostX = this->maxX - this->minX-1;
    int velikostY = this->maxY - this->minY-1;
    int x;
    int y;
    for (int i =0; i<Mnozstvi;i++) {
        do {
            x =rand()%velikostX;
            y =rand()%velikostY;
        }while (x <= this->minX || y <= this->minY || x >= this->maxX || y >= this->maxY);
        PredmetyP.push_back({x,0,y,0});
    }

    for (int i =0; i<PredmetyP.size();i++) {
        this->Bod(PredmetyP[i].x1, PredmetyP[i].y1, '#');
    }
}

void Kresleni::Final(Mistnost &mistnost, std::string PozadovaneD) {

}
void Kresleni::NastavVysledkyBoje(int playerRoll, int playerBonus, int playerTotal, int enemyRoll, int enemyBonus, int enemyTotal,bool victory) {
    lastPlayerRoll = "Hrac hod = " + std::to_string(playerRoll) + " + " + std::to_string(playerBonus) + " = " + std::to_string(playerTotal);

    lastEnemyRoll = "Enemy hod = " + std::to_string(enemyRoll) +
                    " + " + std::to_string(enemyBonus) +
                    " = " + std::to_string(enemyTotal);

    lastBattleResult = victory ? ">>> VYHRAL <<<" : ">>> PROHRAL <<<";
}

void Kresleni::VymazVysledkyBoje() {
    lastPlayerRoll = "";
    lastEnemyRoll = "";
    lastBattleResult = "";
}


