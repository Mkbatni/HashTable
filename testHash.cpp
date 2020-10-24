#include "GeneralStringHasher.cpp"
#include "ProdHasher.cpp"
#include "ChainedHashTable.h"
#include "SumHasher.cpp"
#include <string>
#include <iostream>
#include "Timer.h"
#include <fstream>
using namespace std;

void testConstructor(Hasher* hasher)
{
cout<<"testing constructor" << endl;
ChainedHashTable obj1(5000,hasher);
}

void testCopyConstructor(Hasher* hasher)
{ 
cout<<"testing copy constructor" << endl;

ChainedHashTable obj1(5000,hasher);
 ChainedHashTable obj2 = obj1;
}
            
void testAssignemntOperator(Hasher* hasher)
{ 
cout<<"testing Assignment operator" << endl;

ChainedHashTable obj1(5000,hasher);
 ChainedHashTable obj2 = obj1;
}





void insertAll(Hasher* h,int partition,ifstream& inputFile)
{

ChainedHashTable obj(5000,h);
	string str;
int loopVar = partition*45392/10;
for(int i = 1; i<= loopVar;i++)
{
   getline(inputFile,str);
	obj.insert(str);
}
}                                         

void findAll(Hasher* h,int partition,ifstream& inputFile)
{

ChainedHashTable obj(5000,h);
	string str;
int loopVar = partition*45392/10;
for(int i = 1; i<= loopVar;i++)
{
   getline(inputFile,str);
	obj.find(str);
}
}


void removeAll(Hasher* h,int partition,ifstream& inputFile)
{

	string str;
ChainedHashTable obj(5000,h);
int loopVar = partition*45392/10;
for(int i = 1; i<= loopVar;i++)
{
   getline(inputFile,str);
	obj.remove(str);
}

}



void measure(string file_name)
{
Hasher* h = new GeneralStringHasher;
ifstream in(file_name);
for(int i = 1 ; i <= 10 ; ++i)
{
Timer t1,t2,t3;
double tVar = 0;
t1.start();
insertAll(h,i,in);
t1.elapsedUserTime(tVar);
cout << "testing insert All\n";
cout << tVar << endl;
in.clear();
in.seekg(0,ios::beg);


cout << "testing find All\n";
t2.start();
findAll(h,i,in);
t2.elapsedUserTime(tVar);
cout << tVar << endl;
in.clear();
in.seekg(0,ios::beg);

cout << "testing remove All\n";
t3.start();
removeAll(h,i,in);
t3.elapsedUserTime(tVar);
cout << tVar << endl;
in.clear();
in.seekg(0,ios::beg);

cout<<"\n" << i+1<< "\t-----------------------\n";

}

in.close();
delete h;

}
void insertAllTestHasher(Hasher* h,int partition,ifstream& inputFile)
{

ChainedHashTable obj(5000,h);
	string str;
int loopVar = partition*45392/10;
for(int i = 1; i<= loopVar;i++)
{
   getline(inputFile,str);
	obj.insert(str);
}

cout << "min: " << obj.minChainLength() << "; Max: " << obj.maxChainLength() << "; Average: " 
<< obj.averageChainLength() << "; Std_DeV: " << obj.standardDeviation()<<endl;

}                                         


void testHashFunction(string file_name,Hasher* h,const string& name)
{
cout << "HasherFunction: " << name <<" Chain Length statistics:"<< endl;
ifstream in(file_name);

Timer t1,t2,t3;
double tInsert = 0,tFind = 0,tRemove =0;
t1.start();
insertAllTestHasher(h,10,in);
t1.elapsedUserTime(tInsert);
in.clear();
in.seekg(0,ios::beg);



t2.start();
findAll(h,10,in);
t2.elapsedUserTime(tFind);
in.clear();
in.seekg(0,ios::beg);



t3.start();
removeAll(h,10,in);
t3.elapsedUserTime(tRemove);
in.clear();
in.seekg(0,ios::beg);

cout << "insertALL = " << tInsert << "\nfindAll = " << tFind << "\nremoveAll = " << tRemove << endl;



in.close();

}






int main (int argc, char * argv[])
{

     const char* input_file = argc == 2 ? argv[1] : "random.txt";

Hasher* h = new GeneralStringHasher;
ChainedHashTable obj(10,h);
try
{
//testConstructor(h);
//testCopyConstructor(h);
//testAssignemntOperator(h);
//measure(input_file);
testHashFunction(input_file,h,"General Hash Function");
Hasher* sh = new SumHasher;
testHashFunction(input_file,sh,"SumHasher Hash Function");
Hasher* ph = new ProdHasher;
testHashFunction(input_file,ph,"ProbHasher Hash Function");
delete sh;
delete ph;
}
catch( int i )
{
	cout << i << endl;
}

delete h;
    return 0;
}

