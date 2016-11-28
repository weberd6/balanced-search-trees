CC = g++
CPPFLAGS = -std=c++11 -g

AVLTreeTest: AVLTreeTest.o
	$(CC) $(CPPFLAGS) AVLTreeTest.o -o AVLTreeTest

AVLTreeTest.o: AVLTreeTest.cpp AVLTree.tcc AVLTree.hpp
	$(CC) $(CPPFLAGS) -c AVLTreeTest.cpp

.PHONY: clean

clean:
	rm -rf *.o AVLTreeTest
