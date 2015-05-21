CC=g++

all:
	g++ -c src/main.cpp
	g++ -c src/game_engine.cpp -std=c++0x
	g++ -c src/intro_state.cpp -std=c++0x
	g++ -c src/play_state.cpp -std=c++0x
	g++ -c src/menu_state.cpp -std=c++0x
	g++ -c src/time_manager.cpp -std=c++0x
	g++ -o App main.o game_engine.o intro_state.o play_state.o menu_state.o time_manager.o -W -Wall -pedantic -lSDL -lGLU -lGL

clean:
	rm *.o