all: run-trees

run-trees:  BSTree_main.o BSTree.o
	c++ -g -std=c++11  BSTree_main.o BSTree.o -o run-trees

BSTree.o: BSTree.cpp BSTree.h
	c++ -g -std=c++11 -c BSTree.cpp

BSTree_main.o:  BSTree_main.cpp BSTree.h
	c++ -g -std=c++11 -c BSTree_main.cpp

clean:
	rm *.o run-trees
