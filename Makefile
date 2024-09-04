CC=g++
FLAGS=-lSDL2
BIN=Snake
FILES= ./main.cpp ./s.cpp ./s.hpp

new: 
	$(CC) $(FILES) -o $(BIN) $(FLAGS)
	./$(BIN)
run:
	./$(BIN)
