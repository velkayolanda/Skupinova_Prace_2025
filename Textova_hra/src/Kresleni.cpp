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
    std::cout << "[DEBUG Kresleni] Konstruktor: sirka=" << sirka << ", vyska=" << vyska << "\n";

    // OCHRANA - ujisti se, že rozměry jsou platné
    if (sirka <= 0 || vyska <= 0) {
        std::cerr << "[CHYBA Kresleni] Neplatne rozmery: " << sirka << "x" << vyska << "\n";
        std::cerr << "[INFO Kresleni] Nastavuji minimalni rozmery 40x20\n";
        this->sirka = std::max(40, sirka);
        this->vyska = std::max(20, vyska);
    }

    std::cout << "\033[?25l";
    std::cout << "\033[2J";

    plocha = new char*[this->vyska];
    for (int i = 0; i < this->vyska; i++) {
        plocha[i] = new char[this->sirka];
        for (int j = 0; j < this->sirka; j++) {
            plocha[i][j] = 32;
        }
    }

    std::cout << "[DEBUG Kresleni] Konstruktor dokoncen, plocha " << this->sirka << "x" << this->vyska << " vytvorena\n";
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

    std::cout << "[DEBUG] Zpracovavam " << mistnost.cary.size() << " car\n";

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

    std::cout << "[DEBUG] Rozsah mistnosti: X(" << minX << "-" << maxX
              << "), Y(" << minY << "-" << maxY << ")\n";

    int width  = maxX - minX;
    int height = maxY - minY;

    std::cout << "[DEBUG] Rozmery: width=" << width << ", height=" << height << "\n";

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

    std::cout << "[DEBUG] Cilove rozmery: " << cilovas << "x" << cilovav << "\n";
    std::cout << "[DEBUG] Canvas rozmery: " << sirka << "x" << vyska << "\n";

    // OCHRANA - kontrola platnosti canvas rozměrů
    if (sirka <= 0 || vyska <= 0) {
        std::cerr << "CHYBA: Neplatne rozmery canvas!\n";
        return;
    }

    this->sirkaPZ = static_cast<int>(cilovas);

    float scaleX = cilovas / width;
    float scaleY = cilovav / height;

    std::cout << "[DEBUG] Scale faktory: scaleX=" << scaleX << ", scaleY=" << scaleY << "\n";

    float scale = std::min(scaleX, scaleY);

    std::cout << "[DEBUG] Finalni scale: " << scale << "\n";

    // Kontrola, že scale není neplatné číslo
    if (scale <= 0 || scale != scale) { // scale != scale detekuje NaN
        std::cerr << "CHYBA: Neplatny scale faktoru: " << scale << "\n";
        scale = 1.0f;
        std::cout << "[DEBUG] Nastavuji scale na 1.0\n";
    }

    // DALŠÍ OCHRANA - pokud je scale příliš velký, omez ho
    if (scale > 1000.0f) {
        std::cerr << "VAROVANI: Scale je prilis velky (" << scale << "), omezuji na 10.0\n";
        scale = 10.0f;
    }

    float cx = minX + width  / 2.0f;
    float cy = minY + height / 2.0f;

    std::cout << "[DEBUG] Centrum: (" << cx << ", " << cy << ")\n";
    std::cout << "[DEBUG] Zacatek skalovani...\n";

    // Škálování čar - s kontrolou přetečení
    for (size_t i = 0; i < mistnost.cary.size(); i++) {
        auto& c = mistnost.cary[i];

        float newX1 = cx + (c.x1 - cx) * scale;
        float newX2 = cx + (c.x2 - cx) * scale;
        float newY1 = cy + (c.y1 - cy) * scale;
        float newY2 = cy + (c.y2 - cy) * scale;

        // Kontrola rozsahu
        if (std::abs(newX1) > 10000 || std::abs(newX2) > 10000 ||
            std::abs(newY1) > 10000 || std::abs(newY2) > 10000) {
            std::cerr << "VAROVANI: Cara " << i << " ma extremni souradnice po skalovani\n";
            continue;
        }

        c.x1 = static_cast<int>(newX1);
        c.x2 = static_cast<int>(newX2);
        c.y1 = static_cast<int>(newY1);
        c.y2 = static_cast<int>(newY2);

        if (i < 3) {
            std::cout << "[DEBUG] Cara " << i << " po skalovani: ("
                      << c.x1 << "," << c.y1 << ") -> (" << c.x2 << "," << c.y2 << ")\n";
        }
    }

    // Najdi nové minimum po škálování
    minX = mistnost.cary[0].x1;
    minY = mistnost.cary[0].y1;
    for (auto& c : mistnost.cary) {
        minX = std::min({minX, c.x1, c.x2});
        minY = std::min({minY, c.y1, c.y2});
    }

    std::cout << "[DEBUG] Minimum po skalovani: (" << minX << ", " << minY << ")\n";

    int shiftX = 0;
    int shiftY = 0;

    if (minX < 0) shiftX = -minX;
    if (minY < 0) shiftY = -minY;

    std::cout << "[DEBUG] Posun: (" << shiftX << ", " << shiftY << ")\n";

    // Posun do viditelné oblasti
    if (shiftX != 0 || shiftY != 0) {
        for (auto& c : mistnost.cary) {
            c.x1 += shiftX;
            c.x2 += shiftX;
            c.y1 += shiftY;
            c.y2 += shiftY;
        }
    }

    std::cout << "[DEBUG] Kreslim " << mistnost.cary.size() << " car...\n";

    // Vykreslení čar
    for (size_t i = 0; i < mistnost.cary.size(); i++) {
        auto& c = mistnost.cary[i];

        // Kontrola před kreslením
        if (c.x1 >= 0 && c.x1 < sirka && c.x2 >= 0 && c.x2 < sirka &&
            c.y1 >= 0 && c.y1 < vyska && c.y2 >= 0 && c.y2 < vyska) {
            Cara(c.x1, c.y1, c.x2, c.y2);
        } else {
            std::cerr << "VAROVANI: Cara " << i << " mimo canvas: ("
                      << c.x1 << "," << c.y1 << ") -> (" << c.x2 << "," << c.y2 << ")\n";
        }
    }

    std::cout << "[DEBUG] Kresleni dokonceno\n";
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