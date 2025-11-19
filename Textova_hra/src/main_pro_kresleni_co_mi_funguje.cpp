#include "Kresleni.h"
#include <thread>
#include <chrono>
#include <conio.h>
#include <iostream>

int main() {
    int* columns, *rows;
    columns = new int;
    rows = new int;

    Kresleni::ZiskaniVelikostiConsole(*columns, *rows);
    Kresleni kres(*columns-1,*rows-1);

    Mistnost mistnost(true);
    mistnost.VyberMistnost();

    Mistnost mistnost2(false);
    mistnost2.VyberMistnost("D_Z");

    kres.NacteniMistnosti(mistnost2);
    kres.Psani("Jsi zivy", "Bonus nic", "Prazdy I", "Srajtofle je prazdna");
    std::thread t1(Kresleni::VykresleniThread, kres);
    while (!_kbhit()) {  // animace běží, dokud nestiskneš klávesu

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    t1.join();

    delete columns;
    delete rows;
    return 0;
}
