all: Game.o Main.o output

output: Main.o
	clang++ -std=c++17 Main.o Game.o -o output -lSDL2

Main.o: Main.cpp Game.o
	clang++ -std=c++17 -c Main.cpp

Game.o: Game.cpp Game.h
	clang++ -std=c++17 -c Game.cpp

clean:
	rm *.o output