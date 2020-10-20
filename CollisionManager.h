#pragma once

#ifndef COL_MAN_H
#define COL_MAN_H

#include <vector>
#include <utility>

#include "Components//BoundShape.h"


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager() {};

	bool Collide(BoundShape* b1, BoundShape* b2);

	void HandleCollisions() {};
	void Update();
public:
	std::vector<std::pair<BoundShape*, BoundShape*>> collisions;
private:
private:
	bool (*collideFunctions[NUM_OF_TYPES][NUM_OF_TYPES])(BoundShape* b1, BoundShape* b2);
};


bool AABBAABB(BoundShape* b1, BoundShape* b2);
bool AABBLine(BoundShape* b1, BoundShape* b2);
bool LineAABB(BoundShape* b1, BoundShape* b2);
bool LineLine(BoundShape* b1, BoundShape* b2);



#endif

