#include "../includes/main.h"

int main ( int argc, char *argv[] )
{
	CGameEngine game;
	
	// initialize the engine
	game.SetFullscreen(false);
	game.SetScreenWidth(640);
	game.SetScreenHeight(480);
	
	game.Init("Engine");
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error %s\n", glewGetErrorString(err));
		exit(1);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	if (GLEW_ARB_vertex_program)
		fprintf(stdout, "Status: ARB vertex programs available.\n");

	if (glewGetExtension("GL_ARB_fragment_program"))
		fprintf(stdout, "Status: ARB fragment programs available.\n");

	if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
		fprintf(stdout, "Status: ARB point sprites available.\n");
	
	
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
