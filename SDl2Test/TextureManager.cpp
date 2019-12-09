#include "TextureManager.h"


SDL_Texture* TextureManager::LoadTexture(const char* file) {
	

	SDL_Surface* tempSurf = IMG_Load(file);

	SDL_Texture* tx = SDL_CreateTextureFromSurface(Game::renderer, tempSurf);
	
	SDL_FreeSurface(tempSurf);

	return tx;

}


void TextureManager::Draw(SDL_Texture * tx, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip) {
	
	SDL_RenderCopyEx(Game::renderer, tx, &source, &destination, NULL, NULL, flip);

}