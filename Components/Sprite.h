#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Component.h"

struct SDL_Surface;

class Sprite : public Component
{
public:
	Sprite(GameObject* _owner, char* spritePath);
	~Sprite();

	SDL_Surface* getSprite();
	void newSprite(char* spritePath);

	void Update();
public:
private:
private:
	SDL_Surface* curSprite;
};



#endif

