#include <stdio.h>
#include <fstream>
#include <iostream>

#include "../includes/game_engine.h"
#include "../includes/game_state.h"
#include "../includes/intro_state.h"
#include "../includes/play_state.h"
#include "../includes/time_manager.h"
#include "../includes/model.h"

CIntroState CIntroState::m_IntroState;
Model g_Triangle;

void CIntroState::Init(CGameEngine* game)
{
	angle = 0;
	Vertex3 vertices[] =
	{	//    X 	 Y	   Z      	 R	   G	 B	   A
		{ { -0.6f, -0.6f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { 0.0f, 0.6f, 0.0f },   { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 0.6f, -0.6f, 0.0f },  { 0.0f, 0.0f, 1.0f, 1.0f } }
	};
	
	g_Triangle.Initialize(vertices, 3, "shader/shader.vertex", "shader/shader.fragment");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
	g_Triangle.Destroy();
	
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 3.0, 7.0);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 5.0,
			  0.0, 0.0, 0.0,
			  0.0, 1.0, 0.0);
	
	glRotatef(angle,1.0f, 5.0f, 1.0f );
	//gluOrtho2D(0.0, (GLdouble)game->GetScreenWidth(), 0.0, (GLdouble)game->GetScreenHeight());
	
	g_Triangle.Render();
	angle++;
	

	glFlush();
	SDL_GL_SwapBuffers();
}