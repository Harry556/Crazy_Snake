FLAGS = -pedantic-errors -std=c++11

diff.o: diff.cpp diff.h
	g++ $(FLAGS) -c $<

main.o: main.cpp diff.h
	g++ $(FLAGS) -c $<

game: main.o diff.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f diff.o main.o

.PHONY: clean tar