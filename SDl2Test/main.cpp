#include <SDL.h>
#include <stdio.h>

#include "Game.h"



Game *game = nullptr;

int main(int argc, char *argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("My Game", 800, 640, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

 		frameTime = SDL_GetTicks() - frameStart;


		std::cout << SDL_GetTicks() << std::endl;


		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}


