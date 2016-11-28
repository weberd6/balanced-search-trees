CC = g++
CPPFLAGS = -std=c++11 -g

TwoThreeFourTreeTest: TwoThreeFourTreeTest.o
	$(CC) $(CPPFLAGS) TwoThreeFourTreeTest.o -o TwoThreeFourTreeTest

TwoThreeFourTreeTest.o: TwoThreeFourTreeTest.cpp TwoThreeFourTree.tcc TwoThreeFourTree.hpp
	$(CC) $(CPPFLAGS) -c TwoThreeFourTreeTest.cpp

.PHONY: clean

clean:
	rm -rf *.o TwoThreeFourTreeTest
