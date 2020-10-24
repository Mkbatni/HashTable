#include "ChainedHashTable.h"

ChainedHashTable::ChainedHashTable(const int capacity, Hasher* myHasher)
	:current_capacity{capacity},current_size{0}
{
HashTable = new ListNode*[current_capacity];
for (int i = 0; i < current_capacity; ++i)
{
	HashTable[i] = new ListNode("",0,nullptr);
}
hasher = myHasher;
}
ChainedHashTable::~ChainedHashTable()
{
clearHashTable(current_capacity);
delete[] HashTable;
}
void ChainedHashTable::clearHashTable(int capacity)
{
	for (int i = 0; i < capacity; ++i)
	{
		ListNode* head = HashTable[i];
			ListNode* curr = head->next;
		while(curr != nullptr)
		{
			ListNode* del = curr;
			curr = curr->next;
			delete del;			
		}
		delete head;
		head = nullptr;	
	}
}
ChainedHashTable::ChainedHashTable(const ChainedHashTable& hm)
	:current_capacity{hm.current_capacity},current_size{hm.current_size}
{
	hasher = hm.hasher;
	HashTable = new ListNode*[current_capacity];
	for (int i = 0; i < current_capacity; ++i)
	{
		HashTable[i] = new ListNode(hm.HashTable[i]->key,hm.HashTable[i]->value,nullptr); 
	}

	for (int i = 0; i < current_capacity; ++i)
	{	
		if(hm.HashTable[i]->next != nullptr)
		{
			ListNode* curr = hm.HashTable[i]->next;
			while	(curr != nullptr)
			{
				ListNode* n = new ListNode(curr->key,curr->value,nullptr);
				ListNode* ptr = HashTable[i];
				while (ptr->next != nullptr) ptr = ptr->next;
				ptr->next = n;
				curr = curr->next;
			}

		}

	}
}
ChainedHashTable& ChainedHashTable::operator =(const ChainedHashTable& hm)
{

	if (this != &hm)
	{
ListNode** NewHashTable = new ListNode*[hm.current_capacity];
	int oldCap = current_capacity;



	 current_capacity = hm.current_capacity;
	current_size = hm.current_size;
	for (int i = 0; i < current_capacity; ++i)
{
	NewHashTable[i] = new ListNode("",0,nullptr);
}

	
	for (int i = 0; i < hm.current_capacity; ++i)
	{
		if (hm.HashTable[i]->key != "")
		{
			NewHashTable[i]->key = hm.HashTable[i]->key;
			NewHashTable[i]->value = hm.HashTable[i]->value;
			NewHashTable[i]->next = nullptr;
		
		ListNode* curr = hm.HashTable[i]->next;
		while(curr != nullptr)
			{
				ListNode* n = new ListNode(curr->key,curr->value,nullptr);
				ListNode* p = NewHashTable[i];
				while(p->next != nullptr) p = p->next;
				p->next = n;
				curr = curr->next;
			}
		}
		else NewHashTable[i] =  new ListNode("",0,nullptr);
	}
clearHashTable(oldCap);
	delete[] HashTable;
	HashTable = NewHashTable;
}

	return *this;
}


void ChainedHashTable::insert(const string& key,int value )
{
	unsigned int index = hasher->hash(key,current_capacity);
	if (HashTable[index]->key == "")
	{
		HashTable[index]->key = key;
		HashTable[index]->value = value;
		++current_size;
	}
	else
	{
		ListNode* curr = HashTable[index];
		while(curr->next != nullptr) curr = curr->next;

		ListNode* n = new ListNode(key,value,nullptr);

		curr->next = n;
		++current_size;
	}
}
void ChainedHashTable::print()
{
for (int i = 0; i < current_capacity; ++i)
{
if (HashTable[i]->key != "")
  {
	ListNode* curr = HashTable[i];
	while (curr != nullptr)
	{
cout << curr->key <<endl;
curr = curr->next;
	}
   }
}
}

void ChainedHashTable::remove(const string& key)
{
	unsigned int index = hasher->hash(key,current_capacity);

	ListNode* delPtr = nullptr;

	if(HashTable[index]->key == key && HashTable[index]->next == nullptr)
	{
		HashTable[index]->key = "";
		HashTable[index]->value = 0;
		current_size--;
	}
	else if (HashTable[index]->key == key)
	{
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;
		current_size--;
	}


else
	{

	ListNode*	p1 = HashTable[index]->next;
	ListNode* p2 = HashTable[index];
		while (p1 != nullptr && p1->key != key)
		{
			p2 = p1;
			p1 = p1->next;
		}
	
		if (p1 != nullptr)
		{
			delPtr = p1;
			p1 = p1->next;
			p2->next = p1;
			delete delPtr;
			current_size--;
		}
		
	}
}
int ChainedHashTable::find(const string& key) const
{
	unsigned int index = hasher->hash(key,current_capacity);

	ListNode* curr = HashTable[index];
	while(curr != nullptr)
	{
		if (curr->key == key)
		{
			return curr->value;
		}
		curr = curr->next;
	}
	return -1;
}

int ChainedHashTable::maxChainLength() const
{
	int total = 0;
	for (int i = 0; i < current_capacity; ++i)
	{
	 int count = 0;
		if (HashTable[i]->key != "")
		{
			++count;
			ListNode* ptr = HashTable[i];
			while(ptr->next != nullptr)
			{
				count++;
				ptr = ptr->next;
			}
		}		
		if (total < count) total = count;
	}
	return total;
}

int ChainedHashTable::minChainLength() const
{
	 int total = 0;
	for ( int i = 0; i < current_capacity; ++i)
	{
		int count = 0;
if (HashTable[i]->key != "")
	{
			++count;
			ListNode* ptr = HashTable[i];
			while(ptr->next != nullptr)
			{
				count++;
				ptr = ptr->next;
			}			
	}	

if (total == 0) total = count;
else if(total > count ) total = count; 

	}
return total;
}

double ChainedHashTable::averageChainLength() const
{
int sum = 0;
for(int i = 0; i< current_capacity;i++) sum += bucketSize(i);
return sum / (double) current_capacity;
	//return current_size / (double)current_capacity;
}
double ChainedHashTable::standardDeviation() 
{
	double mean = ChainedHashTable::averageChainLength();
	double standDev = 0;
	double varSum =0;
	double var = 0;
	for (int i = 0; i < current_capacity; ++i)
	{
		varSum += pow(bucketSize(i)-mean,2);
	}
	var = varSum / current_capacity;
	standDev = sqrt(var);
	return standDev;
}


int& ChainedHashTable::operator[](const string& key) 
{

unsigned int index = hasher->hash(key,current_capacity);
ListNode* curr = HashTable[index];
while(curr != nullptr)
	{
		if (curr->key == key) return curr->value;
	  curr = curr->next;
	}
	if (curr == nullptr)
	{
		error("Key not found.");

	}


	return curr->value;


}
