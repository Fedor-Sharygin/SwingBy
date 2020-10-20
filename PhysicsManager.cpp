#include "PhysicsManager.h"
#include "Globals.h"
#include "GameObject.h"

#include "Components//Component.h"


void PhysicsManager::Update()
{
	pCollisionManager->Update();

	for (auto go : pGameObjectManager->mpGameObjects)
		for (auto co : go->mpComponents)
			if (co->type == TYPE_PHYSICS)
				co->Update();
}
