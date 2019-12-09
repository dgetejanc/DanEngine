#include "Game.h"
#include "TextureManager.h"


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0, 800, 640 };

bool Game::isRunning = false;
SDL_Texture* playerTexture;

SDL_Rect playerDestRect;


Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen) {
	int flags = 0;
	
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	playerTexture = TextureManager::LoadTexture("Assets/sprites/player/player-idle/player-idle-3.png");
	
		
}

void Game::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}

}

void Game::update() {
	playerDestRect.h = 64;
	playerDestRect.w = 64;

}

void Game::render() {
	
	SDL_RenderClear(renderer);


	SDL_RenderCopy(renderer, playerTexture, NULL, &playerDestRect);


	SDL_RenderPresent(renderer);

}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}