#pragma once
#include <map>
#include <vector>
#include "string"

struct structMistnost {
    int StartM;
    int EndM;
};

struct Pozice {
    int x1;
    int x2;
    int y1;
    int y2;
};


class Mistnost {

    private:
    std::vector<Mistnost> Mistnosti;
    std::map<std::string, structMistnost> txtmistnost;
    std::vector<std::string> stxtmistnost;
    bool prvni;

    public:
    std::string NacteniMistnosti(std::string PozadovanaM);
    std::string dvere;
    std::vector<Pozice> cary;

    Mistnost(bool prvni);
    void VyberMistnost(std::string PozadovaneD);
    void VyberMistnost();
};
