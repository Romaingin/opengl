CC=g++

all:
	g++ -c src/main.cpp
	g++ -c src/game_engine.cpp -std=c++0x
	g++ -c src/intro_state.cpp -std=c++0x
	g++ -c src/play_state.cpp -std=c++0x
	g++ -c src/menu_state.cpp -std=c++0x
	g++ -c src/time_manager.cpp -std=c++0x
	g++ -c src/model.cpp -std=c++0x
	g++ -c src/shader.cpp -std=c++0x
	g++ -c src/camera.cpp -std=c++0x
	g++ -o App main.o game_engine.o intro_state.o play_state.o menu_state.o time_manager.o model.o shader.o camera.o -W -Wall -pedantic -lSDL -lglut -lGL -lGLU -lGLEW

clean:
	rm *.o