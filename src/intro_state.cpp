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
#include "../includes/inputs.h"

CIntroState CIntroState::m_IntroState;
Model g_Cube;
CCamera g_Camera;

void CIntroState::Init(CGameEngine* game)
{
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

	glViewport (0, 0, (GLsizei) game->GetScreenWidth(), (GLsizei) game->GetScreenHeight());
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode (GL_MODELVIEW);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(50.0, 1.0, 3.0, 30.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(0);

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

	// Keyboard
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				g_keyHandler.handleKeyboardEvent(event.key.keysym.sym, true);
            	break;
			case SDL_KEYUP:
				g_keyHandler.handleKeyboardEvent(event.key.keysym.sym, false);
            	break;
			case SDL_QUIT:
				game->Quit();
				break;
			case SDL_MOUSEMOTION:
				g_mouseHandler.updateCoordinates(event.motion.x, event.motion.y, game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
		}
		if (event.button.button != 0) {
			g_mouseHandler.handleMouseEvent(event.button.button, true);
		} else {
			g_mouseHandler.handleMouseEvent(event.button.button, false);
		}
	}

	SDL_WarpMouse(game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
}

void CIntroState::Update(CGameEngine* game)
{
	double frameRate = TimeManager::Instance().CalculateFrameRate(false);

	if (g_keyHandler.isPressed(SDLK_ESCAPE)) {
		game->Quit();
	}

	float kSpeed = 0.06f;

	if (g_keyHandler.isPressed(SDLK_w)) {
		g_Camera.MoveCamera(kSpeed);
	}
	if (g_keyHandler.isPressed(SDLK_s)) {
		g_Camera.MoveCamera(-kSpeed);
	}
	if (g_mouseHandler.deltaMouseX() != 0 || g_mouseHandler.deltaMouseY() != 0) {
		double deltaX = g_mouseHandler.deltaMouseX() / frameRate * kSpeed;
		double deltaY = g_mouseHandler.deltaMouseY() / frameRate * kSpeed;

		if (deltaX > 10 || deltaX < -10 || deltaX != deltaX) { deltaX = 0; }
		if (deltaY > 10 || deltaY < -10 || deltaY != deltaY) { deltaY = 0; }

		g_Camera.RotateAroundPoint(g_Camera.m_vView, deltaX, 0, 1, 0);
		g_Camera.RotateAroundPoint(g_Camera.m_vView, deltaY, 1, 0, 1);
	}
}


/////// Delete
void Draw3DSGrid()
{
	glColor3ub(0, 255, 0);
	for(float i = -50; i <= 50; i += 1)
	{
		glBegin(GL_LINES);
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);
		glEnd();
	}
}

void CIntroState::Draw(CGameEngine* game)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(g_Camera.m_vPosition.x, g_Camera.m_vPosition.y,  g_Camera.m_vPosition.z,
			  g_Camera.m_vView.x,	  g_Camera.m_vView.y,      g_Camera.m_vView.z,
			  g_Camera.m_vUpVector.x, g_Camera.m_vUpVector.y,  g_Camera.m_vUpVector.z);
	Draw3DSGrid();

	g_Cube.Render();

	glFlush();
	SDL_GL_SwapBuffers();
}
