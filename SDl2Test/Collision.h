#pragma once
#include <SDL.h>

//Laughable easy collsion system. LOL 

class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& RectB);

};

