#include <stdio.h>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../includes/game_engine.h"
#include "../includes/game_state.h"
#include "../includes/menu_state.h"

CMenuState CMenuState::m_MenuState;

void CMenuState::Init(CGameEngine* game)
{
	SDL_Surface* temp = SDL_LoadBMP("res/menu.bmp");

	bg = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);
	/*
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, (GLdouble)640, 0.0, (GLdouble)480);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	*/
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
	SDL_BlitSurface(bg, NULL, game->screen, NULL);
	SDL_UpdateRect(game->screen, 0, 0, 0, 0);
}
