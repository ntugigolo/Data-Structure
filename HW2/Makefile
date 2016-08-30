CC := g++ -O2
FLAGS := -g -Wall -std=c++11
objects = Se.o
all: $(objects) demo
$(objects): %.o: %.cpp
	$(CC) -c $(FLAGS) $< -o $@
demo:
	$(CC) $(FLAGS) -o $@ Se.o

clean:
	rm  *.o demo
