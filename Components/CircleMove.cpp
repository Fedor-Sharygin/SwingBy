#include "CircleMove.h"
#include "Transform.h"

#include "..//GameObject.h"
#include "..//Globals.h"


CircleMove::CircleMove()
	: Component(TYPE_CIRCLE_MOVE), rotationSpeed(20.0f)
{}

CircleMove::~CircleMove()
{}

void CircleMove::Update()
{
	Transform* _goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));
	_goTr->setTilt(_goTr->getTilt() + pFrameRateManager->FrameTime() * sloMo * rotationSpeed);
//	rotationSpeed += 40 * pFrameRateManager->FrameTime() * sloMo;
}

void CircleMove::Serialize(json& j)
{
	auto rs = j.find("rotSpeed");
	if (rs != j.end())
		rotationSpeed = j["rotSpeed"].get<float>();
}

