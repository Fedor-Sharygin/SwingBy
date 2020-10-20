#include "Component.h"
#include "..//GameObject.h"

Component::Component(ComponentType _type)
	: type(_type)
{}

Component::~Component()
{
	mpOwner = NULL;
}
