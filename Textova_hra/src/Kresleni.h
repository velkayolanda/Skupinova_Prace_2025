#pragma once
#include "Mistnost.h"
#include "loot.h"
#include <vector>

class Kresleni {
private:
    int sirka, vyska;
    int sirkaPZ;
    int cx, cy;
    int minX, minY, maxX, maxY;
    char** plocha;
    void VypisText(std::string, int y);
    void VypisText(std::string, int zacatekx, int zacateky);

public:
    Kresleni(int sirka, int vyska);
    ~Kresleni();

    void Vymaz();
    void Bod(int x, int y, char c);
    void Cara(int x1, int y1, int x2, int y2);
    void VykresleniThread(Kresleni& kresleni);
    void Vykresleni(const Kresleni& kresleni);
    static void ZiskaniVelikostiConsole(int& columns, int& rows);
    void NacteniMistnosti(Mistnost& mistnost);
    void PsaniStat(std::string Zivoty, std::string BonusD, std::vector<Item> Item, std::string penize);
    void PsaniEnemy(std::string Jmeno, std::string Popis, std::string souboj);
    void RozmisteniPredmetu(int Mnozstvi);
    void Final(Mistnost& mistnost, std::string PozadovaneD);
};
