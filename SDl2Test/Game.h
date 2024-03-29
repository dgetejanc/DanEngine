#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_image.h>

class Game
{
private:
	int cnt = 0;
	SDL_Window *window;

public:
	Game();
	~Game();
	
	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	
};

