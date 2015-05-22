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
Model g_Cube;

void CIntroState::Init(CGameEngine* game)
{
	angle = 0;
	GLfloat vertices[48] = {
		1.0f, 0.0f, 0.0f, -1.0f, 1.0f, -1.0f,
		1.0f, 0.0f, 1.0f, -1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, -1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f
	};

	GLuint indices[36] = {
		0,1,2,2,1,3,
		4,5,6,6,5,7,
		3,1,5,5,1,7,
		0,2,6,6,2,4,
		6,7,0,0,7,1,
		2,3,4,4,3,5
	};
	
	g_Cube.Initialize(vertices, indices, sizeof(vertices), sizeof(indices), "shader/shader.vertex", "shader/shader.fragment");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
	g_Cube.Destroy();
	
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
	
	g_Cube.Render();
	angle++;
	

	glFlush();
	SDL_GL_SwapBuffers();
}