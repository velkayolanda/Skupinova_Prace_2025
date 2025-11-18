//
// Created by Jar Jar Banton on 18. 11. 2025.
//
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <set>

std::string nactiSoubor(const std::string& nazev) {
    std::ifstream soubor(nazev);
    if (!soubor.is_open()) {
        std::cerr << "CHYBA: Nelze otevrit soubor '" << nazev << "'." << std::endl;
        std::cerr << "Ujistete se, ze jste ho stahli (viz README.md)." << std::endl;
        return "";
    }

    return std::string((std::istreambuf_iterator<char>(soubor)),
                        std::istreambuf_iterator<char>());
}
int analyzujRoboty(const std::string& text) {
    std::regex robot_regex(R"([Rr]obot[\w]*)");
    std::sregex_iterator iterator(text.begin(), text.end(), robot_regex);
    int count = 0;
    while (std::sregex_iterator(iterator) != std::sregex_iterator()) {
        count++;
        iterator++;
    }
    return count;
}

void najdiPrimouRec(const std::string& text) {
    std::regex primluva_regex(R"("[^"]*")");
    std::sregex_iterator iterator(text.begin(), text.end(), primluva_regex);
    std::sregex_iterator end; // End iterator (prázdný)
    int count = 0;
    while (iterator != end && count < 5) {
        std::smatch match = *iterator;

        if (match.size() > 1) {
            std::string prima_rec;
            if (match[1].matched) {
                prima_rec = match[1].str();
            } else if (match[2].matched) {
                prima_rec = match[2].str();
            }


            std::cout << "Prima rec " << count + 1 << ": " << prima_rec << std::endl;
            count++;
        }

        iterator++;
    }
}

void najdiLetopocty(const std::string& text) {
    std::regex letopocet_regex(R"(\b\d{4}\b)");
    std::sregex_iterator iterator(text.begin(), text.end(), letopocet_regex);
    std::cout << "Letopocty:" << std::endl;
    for (std::sregex_iterator i = iterator; i != std::sregex_iterator(); ++i) {
        std::smatch match = *i;
        std::cout << match.str() << std::endl;
    }
}

void najdiPostavy(const std::string& text) {
    // std::regex postava_regex(R"(\n([A-Z][a-z]+):)");
    // std::sregex_iterator iterator(text.begin(), text.end(), postava_regex);
    // std::cout << "Postavy:" << std::endl;
    // for (std::sregex_iterator i = iterator; i != std::sregex_iterator(); ++i) {
    //     std::smatch match = *i;
    //     std::cout << match.str() << std::endl;
    // }
    std::cout << "--- Nalezene postavy (mluvci) ---" << std::endl;
    std::regex re(R"(\n([A-Z][a-z]+):)");

    std::smatch shody;
    std::string::const_iterator startHledani = text.cbegin();
    std::set<std::string> postavy;

    while (std::regex_search(startHledani, text.cend(), shody, re)) {
        postavy.insert(shody[1].str());
        startHledani = shody[0].second;
    }

    for (const auto& postava : postavy) {
        std::cout << postava << ", ";
    }
    std::cout << std::endl << std::endl;
}

int main() {
    std::cout << "Nacitam knihu..." << std::endl;
    std::string text = nactiSoubor("kniha.txt");

    if (text.empty()) {
        return 1; // Konec programu, chyba
    }

    std::cout << "Kniha nactena. Velikost: " << text.length() << " znaku.\n" << std::endl;
    std::cout << "Pocet vyskytu slova Robot a jeho variant: " << analyzujRoboty(text) << std::endl;
    std::cout << "\nPrvnich 5 primych reci:" << std::endl;
    // najdiPrimouRec(text);
    std::cout << std::endl;
    najdiLetopocty(text);
    std::cout << std::endl;
    najdiPostavy(text);

    return 0;
}
