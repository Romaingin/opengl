#include <stdio.h>
#include <iostream>

#include "../includes/game_engine.h"
#include "../includes/game_state.h"
#include "../includes/time_manager.h"
#include "../includes/inputs.h"

KeyboardHandler g_keyHandler;
MouseHandler g_mouseHandler;

void CGameEngine::Init(const char* title)
{
	int flags = 0;
	
	// initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// set the title bar text
	SDL_WM_SetCaption(title, title);

	if ( m_fullscreen ) {
		flags = SDL_FULLSCREEN;
	}
	
	// create the screen surface
	screen = SDL_SetVideoMode(m_width, m_height, 0, SDL_OPENGL | flags);

	m_running = true;
	
	printf("CGameEngine Init\n");
}

void CGameEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if ( m_fullscreen ) {
		screen = SDL_SetVideoMode(640, 480, 0, 0);
	}

	printf("CGameEngine Cleanup\n");

	// shutdown SDL
	SDL_Quit();
}

void CGameEngine::ChangeState(CGameState* state) 
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void CGameEngine::PushState(CGameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void CGameEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void CGameEngine::HandleEvents() 
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void CGameEngine::Update() 
{
	// let the state update the game
	states.back()->Update(this);
}

void CGameEngine::Draw() 
{
	// let the state draw the screen
	states.back()->Draw(this);
}
