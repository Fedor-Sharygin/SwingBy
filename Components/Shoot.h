#pragma once

#ifndef SHOOT_H
#define SHOOT_H

#include "Component.h"


class GameObject;

class Shoot : public Component
{
public:
	Shoot(int _nos = 1, float _tbs = 5.0f)
		: timeBetweenShots(_tbs), noShotTime(_tbs),
		numOfShots(_nos), bulletsShot(_nos),
		Component(TYPE_SHOOT)
	{};
	~Shoot();

	void AcquireTarget();
	void Update();
	void Serialize(json& j);
public:
	float timeBetweenShots;
	float noShotTime;
	int numOfShots;
	int bulletsShot;

	GameObject* target;
private:
private:
};




#endif
