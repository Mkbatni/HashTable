#ifndef GENERALSTRINGHASHER_H
#define GENERALSTRINGHASHER_H
#include <string>
using namespace std;
#include "Hasher.h"
struct GeneralStringHasher : public Hasher
{
virtual int hash(string key, int N) override
{
    const unsigned shift = 6;
const unsigned zero = 0;
    unsigned mask = ~zero >> (32-shift);  // low 6 bits on
    unsigned result = 0;
    int len = (key.size() < 6)?key.size():6;
    for (int i = 0; i < len; i++)
        result = (result << shift) | (key[i] & mask);
    return result % N;
}
};
#endif
