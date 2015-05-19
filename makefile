CC=g++
CFLAGS=-W -Wall -pedantic

all:
	g++ -c src/main.cpp
	g++ -c src/game_engine.cpp
	g++ -c src/intro_state.cpp
	g++ -o App main.o game_engine.o intro_state.o -lglut -lGLU -lGL

clean:
	rm *.o