#include <stdio.h>

#include "../includes/game_engine.h"
#include "../includes/game_state.h"
#include "../includes/intro_state.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
{
	/*
	SDL_Surface* temp = SDL_LoadBMP("intro.bmp");

	bg = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	// create the fader surface like the background with alpha
	fader = SDL_CreateRGBSurface( SDL_SRCALPHA, bg->w, bg->h, 
								  bg->format->BitsPerPixel, 
								  bg->format->Rmask, bg->format->Gmask, 
								  bg->format->Bmask, bg->format->Amask );

	// fill the fader surface with black
	SDL_FillRect (fader, NULL, SDL_MapRGB (bg->format, 0, 0, 0)) ;

	// start off opaque
	alpha = 255;

	SDL_SetAlpha(fader, SDL_SRCALPHA, alpha);
*/
	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
	/*
	SDL_FreeSurface(bg);
	SDL_FreeSurface(fader);
*/
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
	//Events
}

void CIntroState::Update(CGameEngine* game) 
{
	//Update
}

void CIntroState::Draw(CGameEngine* game) 
{
	//Draw
}
