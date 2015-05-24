#include <stdio.h>
#include <fstream>
#include <iostream>

#include "../includes/game_engine.h"
#include "../includes/game_state.h"
#include "../includes/intro_state.h"
#include "../includes/play_state.h"
#include "../includes/time_manager.h"
#include "../includes/camera.h"
#include "../includes/model.h"
#include "../includes/keyboard.h"

CIntroState CIntroState::m_IntroState;
Model g_Cube;
CCamera g_Camera;

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
	g_Camera.PositionCamera(0, 1.5f, 6,   0, 1.5f, 0,   0, 1, 0);
	
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
				g_keyHandler.handleKeyboardEvent(event.key.keysym.sym, true);
            	break;
			case SDL_KEYUP:
				g_keyHandler.handleKeyboardEvent(event.key.keysym.sym, false);
            	break;
		}
	}
}

void CIntroState::Update(CGameEngine* game) 
{
	TimeManager::Instance().CalculateFrameRate(true);
}



/////// Delete
void Draw3DSGrid()
{
	glColor3ub(0, 255, 0);

	// Draw a 1x1 grid along the X and Z axis'
	for(float i = -50; i <= 50; i += 1)
	{
		// Start drawing some lines
		glBegin(GL_LINES);

			// Do the horizontal lines (along the X)
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);

			// Do the vertical lines (along the Z)
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);

		// Stop drawing lines
		glEnd();
	}
}





void CIntroState::Draw(CGameEngine* game) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 3.0, 7.0);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();

	gluLookAt(g_Camera.m_vPosition.x, g_Camera.m_vPosition.y,  g_Camera.m_vPosition.z,	
			  g_Camera.m_vView.x,	  g_Camera.m_vView.y,      g_Camera.m_vView.z,	
			  g_Camera.m_vUpVector.x, g_Camera.m_vUpVector.y,  g_Camera.m_vUpVector.z);
	Draw3DSGrid();
	//glRotatef(angle,1.0f, 5.0f, 1.0f );
	//gluOrtho2D(0.0, (GLdouble)game->GetScreenWidth(), 0.0, (GLdouble)game->GetScreenHeight());
	
	g_Cube.Render();
	angle++;

	glFlush();
	SDL_GL_SwapBuffers();
}