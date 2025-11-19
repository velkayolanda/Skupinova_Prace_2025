#pragma once
#include "Mistnost.h"

class Kresleni {
private:
    int sirka, vyska;
    int sirkaPZ;
    char** plocha;

public:
    Kresleni(int sirka, int vyska);
    ~Kresleni();

    void Vymaz();
    void Bod(int x, int y, char c);
    void Cara(int x1, int y1, int x2, int y2);
    static void VykresleniThread(Kresleni kresleni);
    void Vykresleni(const Kresleni& kresleni);
    static void ZiskaniVelikostiConsole(int& columns, int& rows);
    void NacteniMistnosti(Mistnost& mistnost);
    void Psani(std::string Zivoty, std::string BonusD, std::string Item, std::string penize);
    void VypisText(std::string, int y);
    void RozmisteniPredmetu();

};
