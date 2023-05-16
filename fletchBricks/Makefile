all: Game.o main.o output

output: main.o
	clang++ -std=c++17 main.o Game.o -o output -lSDL2

main.o: main.cpp Game.o
	clang++ -std=c++17 -c main.cpp

Game.o: Game.cpp Game.h
	clang++ -std=c++17 -c Game.cpp

clean:
	rm *.o output