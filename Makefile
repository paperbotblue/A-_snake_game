CC=g++
FLAGS=-lSDL2
BIN=Snake
FILES= ./main.cpp ./s.cpp ./s.hpp ./A_star_algorithm.cpp ./A_star_algorithm.hpp

new: 
	$(CC) $(FILES) -o $(BIN) $(FLAGS)
	./$(BIN)
run:
	./$(BIN)
