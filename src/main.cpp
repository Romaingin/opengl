#include "../includes/main.h"

int main ( int argc, char *argv[] )
{
	CGameEngine game;
	
	// initialize the engine
	game.SetFullscreen(false);
	game.SetScreenWidth(640);
	game.SetScreenHeight(480);
	
	game.Init("Engine");

	// load the intro
	game.ChangeState(CIntroState::Instance());

	// main loop
	while (game.Running())
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

	// cleanup the engine
	game.Cleanup();
	return 0;
}

/*
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.25, 0.0);
	glVertex3f(0.75, 0.25, 0.0);
	glVertex3f(0.75, 0.75, 0.0);
	glVertex3f(0.25, 0.75, 0.0);
	glEnd();
	glFlush();
}

void init (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	
}*/
