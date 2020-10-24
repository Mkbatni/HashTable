#ifndef HASHER_H
#define HASHER_H
#include <string>
using namespace std;
struct Hasher
{
	virtual ~Hasher() = default;
	virtual int hash(string s, int n) = 0;
};

#endif