//
// Created by honzi on 7. 11. 2025.
//

//advent of code 2017 day 15

#include <iostream>
#include <cstdint>

using namespace std;

const uint64_t FactorA = 16807;
const uint64_t FactorB = 48271;
const uint64_t Divisor = 2147483647;

const int pairs = 40000000;

inline bool match(uint64_t a, uint64_t b){
    return (a & 0xFFFF) ==(b & 0xFFFF);
}

int main()
{
    uint64_t a = 591;
    uint64_t b = 393;

    int zhody = 0;
    for (int i = 0; i < pairs; i++)
    {
        a = (a*FactorA) % (Divisor);
        b = (b*FactorB) % (Divisor);
        if ((a & 0xFFFF) ==(b & 0xFFFF))
        {
            zhody++;
        }
    }
    cout<<"zhody z part 1: "<<zhody<<endl;
}