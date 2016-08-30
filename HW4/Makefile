CC := g++
FLAGS := -g -Wall -std=c++11
objects = tree_2.o forest.o
all: $(objects) forest tree
$(objects): %.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@
forest: forest.cpp
	$(CC) $(FLAGS) -o $@  forest.o
tree: tree_2.cpp
	$(CC) $(FLAGS) -o $@ tree_2.o

clean:
	rm *.o tree forest

