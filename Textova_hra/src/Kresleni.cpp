//
// Created by Lukas on 11.11.2025.
//

#include "Kresleni.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <algorithm>
#include <conio.h>
#include <cmath>
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
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
            plocha[y1][x] = '-';
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

void Kresleni::VykresleniThread(Kresleni kresleni) {
    while (!_kbhit()) {
        kresleni.Vykresleni(kresleni);
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
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
    // Kontrola, jestli místnost má nějaké čáry
    if (mistnost.cary.empty()) {
        std::cerr << "CHYBA: Mistnost nema zadne cary!\n";
        return;
    }

    int minX = mistnost.cary[0].x1;
    int maxX = mistnost.cary[0].x1;
    int minY = mistnost.cary[0].y1;
    int maxY = mistnost.cary[0].y1;

    for (auto& c : mistnost.cary) {
        minX = std::min({minX, c.x1, c.x2});
        maxX = std::max({maxX, c.x1, c.x2});
        minY = std::min({minY, c.y1, c.y2});
        maxY = std::max({maxY, c.y1, c.y2});
    }

    int width  = maxX - minX;
    int height = maxY - minY;

    // OCHRANA PROTI DĚLENÍ NULOU
    if (width <= 0) {
        std::cerr << "VAROVANI: Mistnost ma nulovou sirku, nastavuji na 10\n";
        width = 10;
    }
    if (height <= 0) {
        std::cerr << "VAROVANI: Mistnost ma nulovou vysku, nastavuji na 10\n";
        height = 10;
    }

    float cilovas = (sirka  * 0.75f);
    float cilovav = (vyska  * 0.75f);

    this->sirkaPZ = static_cast<int>(cilovas);

    float scaleX = cilovas / width;
    float scaleY = cilovav / height;

    float scale = std::min(scaleX, scaleY);

    // Kontrola, že scale není neplatné číslo
    if (scale <= 0 || scale != scale) { // scale != scale detekuje NaN
        std::cerr << "CHYBA: Neplatny scale faktoru: " << scale << "\n";
        scale = 1.0f;
    }

    float cx = minX + width  / 2.0f;
    float cy = minY + height / 2.0f;

    // Škálování čar
    for (auto& c : mistnost.cary) {
        c.x1 = static_cast<int>(cx + (c.x1 - cx) * scale);
        c.x2 = static_cast<int>(cx + (c.x2 - cx) * scale);
        c.y1 = static_cast<int>(cy + (c.y1 - cy) * scale);
        c.y2 = static_cast<int>(cy + (c.y2 - cy) * scale);
    }

    // Najdi nové minimum po škálování
    minX = mistnost.cary[0].x1;
    minY = mistnost.cary[0].y1;
    for (auto& c : mistnost.cary) {
        minX = std::min({minX, c.x1, c.x2});
        minY = std::min({minY, c.y1, c.y2});
    }

    int shiftX = 0;
    int shiftY = 0;

    if (minX < 0) shiftX = -minX;
    if (minY < 0) shiftY = -minY;

    // Posun do viditelné oblasti
    if (shiftX != 0 || shiftY != 0) {
        for (auto& c : mistnost.cary) {
            c.x1 += shiftX;
            c.x2 += shiftX;
            c.y1 += shiftY;
            c.y2 += shiftY;
        }
    }

    // Vykreslení čar
    for (auto& c : mistnost.cary) {
        Cara(c.x1, c.y1, c.x2, c.y2);
    }
}

void Kresleni::VypisText(std::string Text, int y) {
    int zacatek = sirkaPZ + 2;

    // Kontrola hraníc
    if (y < 0 || y >= vyska) return;
    if (zacatek >= sirka) return;

    for (size_t i = 0; i < Text.size() && (zacatek + i) < sirka; i++) {
        plocha[y][zacatek + i] = Text[i];
    }
}

void Kresleni::Psani(std::string Zivoty, std::string BonusD, std::string Item, std::string penize) {
    std::vector<std::string> text = {
        "Statistika: ",
        "Mas zivotu: " + Zivoty,
        "Bonus damage: " + BonusD,
        "Item: " + Item,
        "Penize: " + penize
    };

    for (size_t i = 0; i < text.size(); i++) {
        VypisText(text[i], static_cast<int>(i));
    }
}