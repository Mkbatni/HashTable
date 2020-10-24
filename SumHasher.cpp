#ifndef SUMHASHER_H
#define SUMHASHER_H
#include <string>
using namespace std;
#include "Hasher.h"
#include <algorithm>
struct SumHasher : Hasher {
virtual int hash(string s, int N) override
{
        int result = 0;
        for (unsigned int i=0; i<s.size(); ++i)
            result += s[i];
        return abs(result) % N;
	
    }
};




#endif
