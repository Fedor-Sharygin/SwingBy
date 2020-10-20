#include "CollisionManager.h"
#include "Managers.h"
#include "GameObject.h"


CollisionManager::CollisionManager()
{
	collideFunctions[TYPE_AABB][TYPE_AABB] = AABBAABB;
	collideFunctions[TYPE_AABB][TYPE_LINE] = AABBLine;

	collideFunctions[TYPE_LINE][TYPE_AABB] = LineAABB;
	collideFunctions[TYPE_LINE][TYPE_LINE] = LineLine;
}

bool CollisionManager::Collide(BoundShape* b1, BoundShape* b2)
{
	return collideFunctions[b1->bsType][b2->bsType](b1, b2);
}

void CollisionManager::Update()
{
	collisions.clear();

	for (auto go : pGameObjectManager->mpGameObjects)
		for (auto co : go->mpComponents)
			if (co->type == TYPE_BOUND_SHAPE)
				co->Update();

	for (auto go1 = pGameObjectManager->mpGameObjects.begin();
		go1 != pGameObjectManager->mpGameObjects.end(); ++go1)
	{
		BoundShape* bod1 = static_cast<BoundShape*>((*go1)->getComponent(TYPE_BOUND_SHAPE));
		if (nullptr != bod1)
		{
			for (auto go2 = std::next(go1);
				go2 != pGameObjectManager->mpGameObjects.end(); ++go2)
			{
				BoundShape* bod2 = static_cast<BoundShape*>((*go2)->getComponent(TYPE_BOUND_SHAPE));
				if (nullptr != bod2)
				{
					if (Collide(bod1, bod2))
					{
						int i = 0;
						if (((*go1)->type == TYPE_PLAYER && (*go2)->type == TYPE_BLADE)
							|| ((*go1)->type == TYPE_BLADE && (*go2)->type == TYPE_PLAYER))
						{
							Event* bladeHit = new Event(TYPE_PL_BLADE_COLL);
							bladeHit->participants.push_back(*go1);
							bladeHit->participants.push_back(*go2);
							pEventManager->addEvent(bladeHit);
						}
						else
						if (((*go1)->type == TYPE_PLAYER && (*go2)->type == TYPE_BULLET)
							|| ((*go1)->type == TYPE_BULLET && (*go2)->type == TYPE_PLAYER))
						{
							Event* bulletHit = new Event(TYPE_PL_BULLET_COLL);
							bulletHit->participants.push_back(*go1);
							bulletHit->participants.push_back(*go2);
							pEventManager->addEvent(bulletHit);
						}
						else
						if (((*go1)->type == TYPE_PLAYER && (*go2)->type == TYPE_BOOSTER)
							|| ((*go1)->type == TYPE_BOOSTER && (*go2)->type == TYPE_PLAYER))
						{
							Event* boostHit = new Event(TYPE_PL_BOOSTER_COLL);
							boostHit->participants.push_back(*go1);
							boostHit->participants.push_back(*go2);
							pEventManager->addEvent(boostHit);
						}
						collisions.push_back(std::make_pair(bod1, bod2));
					}
				}
			}
		}
	}

	//std::cout << "Number of collisions is " << collisions.size() << std::endl;
}


bool AABBAABB(BoundShape* b1, BoundShape* b2)
{
	bool ifBoost = ((b1->mpOwner->type == TYPE_BOOSTER) || (b2->mpOwner->type == TYPE_BOOSTER));

	AABB* ab1 = static_cast<AABB*>(b1);
	AABB* ab2 = static_cast<AABB*>(b2);

	if ((ab1->mCenter.x + ab1->width / 2.0f < ab2->mCenter.x - ab2->width / 2.0f)
		|| (ab2->mCenter.x + ab2->width / 2.0f < ab1->mCenter.x - ab1->width / 2.0f)
		|| (ab1->mCenter.y + ab1->height / 2.0f < ab2->mCenter.y - ab2->height / 2.0f)
		|| (ab2->mCenter.y + ab2->height / 2.0f < ab1->mCenter.y - ab1->height / 2.0f))
		return false;

	return true;
}

bool AABBLine(BoundShape* b1, BoundShape* b2)
{
	AABB* ab1 = static_cast<AABB*>(b1);
	Line* li2 = static_cast<Line*>(b2);

	Line* abSide;

	abSide = new Line();
	abSide->start = glm::vec2(ab1->mCenter.x - ab1->width / 2.0f,
							  ab1->mCenter.y + ab1->height / 2.0f);
	abSide->tilt = 180.0f;
	abSide->length = ab1->height;

	if (LineLine(abSide, li2))
		return true;

	delete abSide;


	abSide = new Line();
	abSide->start = glm::vec2(ab1->mCenter.x - ab1->width / 2.0f,
							  ab1->mCenter.y - ab1->height / 2.0f);
	abSide->tilt = 90.0f;
	abSide->length = ab1->width;

	if (LineLine(abSide, li2))
		return true;

	delete abSide;


	abSide = new Line();
	abSide->start = glm::vec2(ab1->mCenter.x + ab1->width / 2.0f,
							  ab1->mCenter.y - ab1->height / 2.0f);
	abSide->tilt = 0.0f;
	abSide->length = ab1->height;

	if (LineLine(abSide, li2))
		return true;

	delete abSide;


	abSide = new Line();
	abSide->start = glm::vec2(ab1->mCenter.x + ab1->width / 2.0f,
		ab1->mCenter.y + ab1->height / 2.0f);
	abSide->tilt = -90.0f;
	abSide->length = ab1->width;

	if (LineLine(abSide, li2))
		return true;

	delete abSide;


	return false;
}

bool LineAABB(BoundShape* b1, BoundShape* b2)
{
	return AABBLine(b2, b1);
}

bool LineLine(BoundShape* bs1, BoundShape* bs2)
{
	Line* li1 = static_cast<Line*>(bs1);
	Line* li2 = static_cast<Line*>(bs2);

	glm::vec2 line1 = li1->length * glm::vec2(sinf(glm::radians(li1->tilt)),
											  cosf(glm::radians(li1->tilt)));
	glm::vec2 line2 = li2->length * glm::vec2(sinf(glm::radians(li2->tilt)),
											  cosf(glm::radians(li2->tilt)));

	float dx1 = line1.x, dy1 = line1.y;
	float dx2 = line2.x, dy2 = line2.y;

	if (dx1 == 0 && dx2 == 0)
	{
		return (li1->start.x == li2->start.x);
	}
	else
	if (dx1 == 0)
	{
		float a2 = dy2 / dx2;
		float b2 = li2->start.y - a2 * li2->start.x;

		glm::vec2 intersectionPoint = glm::vec2(li1->start.x, a2 * li1->start.x + b2);
		glm::vec2 fDir1 = intersectionPoint - li1->start, sDir1 = fDir1 - line1;
		glm::vec2 fDir2 = intersectionPoint - li2->start, sDir2 = fDir2 - line2;
		return ((glm::dot(fDir1, sDir1) < 0) && (glm::dot(fDir2, sDir2) < 0));
	}
	else
	if (dx2 == 0)
	{
		float a1 = dy1 / dx1;
		float b1 = li1->start.y - a1 * li1->start.x;

		glm::vec2 intersectionPoint = glm::vec2(li2->start.x, a1 * li2->start.x + b1);
		glm::vec2 fDir1 = intersectionPoint - li1->start, sDir1 = fDir1 - line1;
		glm::vec2 fDir2 = intersectionPoint - li2->start, sDir2 = fDir2 - line2;
		return ((glm::dot(fDir1, sDir1) < 0) && (glm::dot(fDir2, sDir2) < 0));
	}

	float a1 = dy1 / dx1;
	float b1 = li1->start.y - a1 * li1->start.x;
	float a2 = dy2 / dx2;
	float b2 = li2->start.y - a2 * li2->start.x;

	if (a1 == a2)
		return false;

	float intersectionX = (b2 - b1) / (a1 - a2);

	glm::vec2 intersectionPoint = glm::vec2(intersectionX, a1 * intersectionX + b1);
	glm::vec2 fDir1 = intersectionPoint - li1->start, sDir1 = fDir1 - line1;
	glm::vec2 fDir2 = intersectionPoint - li2->start, sDir2 = fDir2 - line2;
	return ((glm::dot(fDir1, sDir1) < 0) && (glm::dot(fDir2, sDir2) < 0));
}


