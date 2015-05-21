#include <stdio.h>

#include <SDL/SDL.h>

#include "../includes/game_engine.h"
#include "../includes/game_state.h"
#include "../includes/menu_state.h"

CMenuState CMenuState::m_MenuState;

void CMenuState::Init(CGameEngine* game)
{
	printf("CMenuState Init\n");
}

void CMenuState::Cleanup()
{
	SDL_FreeSurface(bg);

	printf("CMenuState Cleanup\n");
}

void CMenuState::Pause()
{
	printf("CMenuState Pause\n");
}

void CMenuState::Resume()
{
	printf("CMenuState Resume\n");
}

void CMenuState::HandleEvents(CGameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						game->PopState();
						break;
				}
				break;
		}
	}
}

void CMenuState::Update(CGameEngine* game) 
{

}

void CMenuState::Draw(CGameEngine* game) 
{
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, (GLdouble)game->GetScreenWidth(), 0.0, (GLdouble)game->GetScreenHeight());
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor4f(0,0,0,0.5);
	glBegin(GL_QUADS);
		glVertex2f(0, 400);
		glVertex2f(0, 0);
		glVertex2f(600, 0);
		glVertex2f(600, 400);
	glEnd();
	
	glFlush();
	SDL_GL_SwapBuffers();
}
