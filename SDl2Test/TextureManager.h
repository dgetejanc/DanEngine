#pragma once
#include "Game.h";

class TextureManager
{

public:
	static SDL_Texture* LoadTexture(const char* file);
	static void Draw(SDL_Texture* tx, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip);
};

