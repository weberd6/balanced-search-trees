CC = g++
CPPFLAGS = -std=c++11 -g

RBTreeTest: RBTreeTest.o
	$(CC) $(CPPFLAGS) RBTreeTest.o -o RBTreeTest

RBTreeTest.o: RBTreeTest.cpp RBTree.tcc RBTree.hpp
	$(CC) $(CPPFLAGS) -c RBTreeTest.cpp

.PHONY: clean

clean:
	rm -rf *.o RBTreeTest
