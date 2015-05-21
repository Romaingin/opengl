#include <stdio.h>

#include <SDL/SDL.h>
#include "../includes/game_state.h"
#include "../includes/game_engine.h"
#include "../includes/play_state.h"
#include "../includes/menu_state.h"

CPlayState CPlayState::m_PlayState;

void CPlayState::Init(CGameEngine* game)
{
	printf("CPlayState Init\n");
}

void CPlayState::Cleanup()
{
	SDL_FreeSurface(bg);

	printf("CPlayState Cleanup\n");
}

void CPlayState::Pause()
{
	printf("CPlayState Pause\n");
}

void CPlayState::Resume()
{
	printf("CPlayState Resume\n");
}

void CPlayState::HandleEvents(CGameEngine* game)
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
						game->Quit();
						break;
					case SDLK_m:
						game->PushState( CMenuState::Instance() );
						break;
				}
				break;
		}
	}
}

void CPlayState::Update(CGameEngine* game)
{

}

void CPlayState::Draw(CGameEngine* game)
{
	
}

