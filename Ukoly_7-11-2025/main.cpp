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

const int pairs_part1 = 40000000;
const int pairs_part2 = 50000000;

inline bool match(uint64_t a, uint64_t b)
{
    return (a & 0xFFFF) ==(b & 0xFFFF);
}
uint64_t part_1(uint64_t startA, uint64_t startB)
{
    uint64_t a = startA, b = startB;
    uint64_t shody = 0;
    for (int i = 0; i < pairs_part1; i++)
    {
        a = (a*FactorA) % (Divisor);
        b = (b*FactorB) % (Divisor);
        if (match(a, b))
        {
            shody++;
        }
        return shody;
    }
}
    uint64_t part2(uint64_t startA, uint64_t startB){
        uint64_t a = startA, b = startB;
        uint64_t shody = 0;
        int pary = 0;
        while (pary < pairs_part2)
        {
            do
            {
                a = (a*FactorA) % (Divisor);
            }
            while (a%4 != 0);
            do
            {
                b = (a*FactorB) % (Divisor);
            }
            while (b%8 != 0);
            if (match(a, b)) shody++;
            pary++;
        }
        return shody;

    }
int main()
{
    uint64_t startA = 591;
    uint64_t startB = 393;
    uint64_t vysledek_part1 = part_1(startA,startB);
    uint64_t vysledek_part2 = part2(startA,startB);
    cout<<"shody z part 1: "<<vysledek_part1<<endl;
    cout<<"shody z part 2: " <<vysledek_part2<<endl;
    return 0;
}