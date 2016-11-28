CC = g++
CPPFLAGS = -std=c++11 -g

AATreeTest: AATreeTest.o
	$(CC) $(CPPFLAGS) AATreeTest.o -o AATreeTest

AATreeTest.o: AATreeTest.cpp AATree.tcc AATree.hpp
	$(CC) $(CPPFLAGS) -c AATreeTest.cpp

.PHONY: clean

clean:
	rm -rf *.o AATreeTest
