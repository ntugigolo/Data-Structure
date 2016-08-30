CC := g++ -O3
FLAGS := -g -Wall -std=c++11
objects = T.o
all: $(objects) system
$(objects): %.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@
system: T.cpp
	$(CC) $(FLAGS) -o $@  T.o
clean:
	rm *.o system
