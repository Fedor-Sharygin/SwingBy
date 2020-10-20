#include "Sprite.h"
#include "..//Managers.h"


Sprite::Sprite(GameObject* _owner, char* spritePath)
	: Component(_owner, TYPE_SPRITE)
{
	curSprite = pResourceManager->LoadSurface(spritePath);
}

Sprite::~Sprite()
{
	delete curSprite;
}

void Sprite::Update()
{}

SDL_Surface* Sprite::getSprite()
{
	return curSprite;
}

void Sprite::newSprite(char* spritePath)
{
	delete curSprite;
	curSprite = pResourceManager->LoadSurface(spritePath);
}


