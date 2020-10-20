#include "Shoot.h"
#include "Transform.h"
#include "Physics.h"

#include "..//GameObject.h"
#include "..//Globals.h"
#include "..//Serial.h"


Shoot::~Shoot()
{
	target = NULL;
}

void Shoot::AcquireTarget()
{
	GameObject* tar = pGameObjectManager->getGO(TYPE_PLAYER);
	if (nullptr == tar)
	{
		target = nullptr;
	}
	else
	{
		Transform* tarTr = static_cast<Transform*>(tar->getComponent(TYPE_TRANSFORM));
		Transform* shTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));

		if (shTr->getPosition().z < tarTr->getPosition().z)
			target = nullptr;
		else
		{
			glm::vec3 disPos = shTr->getPosition() - tarTr->getPosition();
			float distance = sqrtf(glm::dot(disPos,disPos));

			if (distance > 3.0f * pScrWidth / 16.0f)
				target = nullptr;
			else
				target = tar;
		}
	}
}

void Shoot::Update()
{
	if (nullptr != target)
	{
		Transform* targetTr = static_cast<Transform*>(target->getComponent(TYPE_TRANSFORM));
		Transform* shTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));
		if (shTr->getPosition().z <= targetTr->getPosition().z)
		{
			target = NULL;
		}
		else
		if (bulletsShot > 0 && sloMo != 0.0f)
		{
			--bulletsShot;

			GameObject* bullet = Serial::goFactory->createBullet();
			Physics* bPh = static_cast<Physics*>(bullet->getComponent(TYPE_PHYSICS));
			Transform* bTr = static_cast<Transform*>(bullet->getComponent(TYPE_TRANSFORM));
			AABB* bBS = static_cast<AABB*>(bullet->getComponent(TYPE_BOUND_SHAPE));

			bTr->setPosition(shTr->getPosition());
			bBS->mCenter = glm::vec2(shTr->getPosition().z, shTr->getPosition().y) - glm::vec2(3.5f, 0.0f);

			glm::vec3 direction = glm::normalize(targetTr->getPosition() - bTr->getPosition());

			bPh->speed = 50.0f * direction;

			pGameObjectManager->addGameObject(bullet);
		}
		else
		if (noShotTime > 0)
			noShotTime -= pFrameRateManager->FrameTime() * sloMo;
		else
		{
			noShotTime = timeBetweenShots;
			bulletsShot = numOfShots;
		}
	}
	else
		AcquireTarget();
}

void Shoot::Serialize(json& j)
{
	auto tbs = j.find("Wait time");
	if (tbs != j.end())
		timeBetweenShots = noShotTime = j["Wait time"].get<float>();

	auto nos = j.find("Clip");
	if (nos != j.end())
		numOfShots = bulletsShot = j["Clip"].get<int>();
}


