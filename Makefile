CXXFLAGS=-std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant 
CFLAGS=-std=c99 -Wall -Wextra -Werror -ansi -Wwrite-strings

main:
	echo     ------------compiling testHash.cpp create executable program test_hash----------------
	g++ -ggdb $(CXXFLAGS) testHash.cpp ChainedHashTable.cpp GeneralStringHasher.cpp ProdHasher.cpp SumHasher.cpp -o main
	
clean:
	echo ----------------removing executable program test_queue--------------------
	/bin/rm main
