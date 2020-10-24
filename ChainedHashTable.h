#ifndef CHAINEDHASHTABLE_H
#define CHAINEDHASHTABLE_H

#include <string>
#include <iostream>
#include <cmath>
#include "GeneralStringHasher.cpp"
using namespace std;
class ChainedHashTable
{
public:
//using Hasher = function< int(const string&, int N)>;

	ChainedHashTable(const int capacity, Hasher* myHasher);
	~ChainedHashTable();
 	ChainedHashTable(const ChainedHashTable& hm);
 	ChainedHashTable& operator=(const ChainedHashTable& hm);




void insert(const std::string& key, int value = 1);
void print();
void clearHashTable( int capacity);
void remove(const string&);
int find(const string&) const;

int maxChainLength() const;
int minChainLength() const;
double averageChainLength()const ;
double standardDeviation() ;
int bucketSize(int bucket) const
{
	int count = 0;
	if (HashTable[bucket]->key != "")
	{
			++count;
			ListNode* ptr = HashTable[bucket];
			while(ptr->next != nullptr)
			{
				count++;
				ptr = ptr->next;
			}			
	}	
	return count;
}


int getSize()
{
	return current_size;
}
int getCapacity()
{
	return current_capacity;
}

    int& operator[](const string&) ;
private:
  struct ListNode
    {
        std::string key;
        int value;
        ListNode* next;
 ListNode(const string keyGiven,const int valueGiven,ListNode* get_next)
 :key{keyGiven},value{valueGiven},next{get_next}
 {
 }
    };

 int current_capacity;
 int current_size;
ListNode** HashTable ;    


 
void error(const string& str)
{
	cerr << "Error: " << str <<endl;
	throw 0;
}

Hasher* hasher;

};




#endif
