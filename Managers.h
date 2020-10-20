#pragma once

#ifndef _MANAGERS_H_
#define _MANAGERS_H_

#include "FrameRateManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "EventManager.h"

class InputManager;

extern FrameRateManager* pFrameRateManager;
extern ResourceManager* pResourceManager;
extern InputManager* pInputManager;
extern GameObjectManager* pGameObjectManager;
extern CollisionManager* pCollisionManager;
extern PhysicsManager* pPhysicsManager;

extern EventManager* pEventManager;
extern std::unordered_map<EventType, std::vector<GameObject*>> eventSubscribers;

#endif

