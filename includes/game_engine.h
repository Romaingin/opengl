#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

class CGameState;

class CGameEngine
{
public:
	void Init(const char* title);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	// Getters
	bool Running() { return m_running; }
	bool GetFullscreen() { return m_fullscreen; }
	int GetScreenWidth() { return m_width; }
	int GetScreenHeight() { return m_height; }
	
	// Setters
	void SetFullscreen(bool val) { m_fullscreen = val; }
	void SetScreenWidth(int val) { m_width = val; }
	void SetScreenHeight(int val) { m_height = val; }
	void Quit() { m_running = false; }

	SDL_Surface* screen;

private:
	// the stack of states
	vector<CGameState*> states;

	bool m_running;
	bool m_fullscreen;
	int m_width;
	int m_height;
};

#endif