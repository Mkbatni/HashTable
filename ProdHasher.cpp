#ifndef PRODHASHER_H
#define PRODHASHER_H
#include <string>
#include <algorithm>
using namespace std;
#include "Hasher.h"
struct ProdHasher : Hasher {
  virtual  int hash(string s, int N) override 
  {
        int result = 1;
        for (unsigned int i=0; i<s.size(); ++i)
            result *= s[i];
        return abs(result) % N;
    }
};
#endif
