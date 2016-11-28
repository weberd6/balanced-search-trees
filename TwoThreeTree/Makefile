CC = g++
CPPFLAGS = -std=c++11 -g

TwoThreeTreeTest: TwoThreeTreeTest.o
	$(CC) $(CPPFLAGS) TwoThreeTreeTest.o -o TwoThreeTreeTest

TwoThreeTreeTest.o: TwoThreeTreeTest.cpp TwoThreeTree.tcc TwoThreeTree.hpp
	$(CC) $(CPPFLAGS) -c TwoThreeTreeTest.cpp

.PHONY: clean

clean:
	rm -rf *.o TwoThreeTreeTest
