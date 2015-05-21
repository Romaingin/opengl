#include <stdio.h>
#include <fstream>
#include <iostream>

#include "../includes/game_engine.h"
#include "../includes/game_state.h"
#include "../includes/intro_state.h"
#include "../includes/play_state.h"
#include "../includes/time_manager.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init(CGameEngine* game)
{	
	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
	printf("CIntroState Cleanup\n");
}

void CIntroState::Pause()
{
	printf("CIntroState Pause\n");
}

void CIntroState::Resume()
{
	printf("CIntroState Resume\n");
}

void CIntroState::HandleEvents(CGameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						game->ChangeState( CPlayState::Instance() );
						break;

					case SDLK_ESCAPE:
						game->Quit();
						break;
				}
				break;
		}
	}
}

void CIntroState::Update(CGameEngine* game) 
{
	TimeManager::Instance().CalculateFrameRate(true);
}

void CIntroState::Draw(CGameEngine* game) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)game->GetScreenWidth(), 0.0, (GLdouble)game->GetScreenHeight());
	glDisable(GL_DEPTH_TEST);
	
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