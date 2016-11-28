CC = g++
CPPFLAGS = -std=c++11 -g

BinarySearchTreeTest: BinarySearchTreeTest.o
	$(CC) $(CPPFLAGS) BinarySearchTreeTest.o -o BinarySearchTreeTest

BinarySearchTreeTest.o: BinarySearchTreeTest.cpp BinarySearchTree.tcc BinarySearchTree.hpp
	$(CC) $(CPPFLAGS) -c BinarySearchTreeTest.cpp

.PHONY: clean

clean:
	rm -rf *.o BinarySearchTreeTest
