#include "Managers.h"

FrameRateManager* pFrameRateManager = new FrameRateManager(60);
InputManager* pInputManager = new InputManager();
ResourceManager* pResourceManager = new ResourceManager();
GameObjectManager* pGameObjectManager = new GameObjectManager();
CollisionManager* pCollisionManager = new CollisionManager();
PhysicsManager* pPhysicsManager = new PhysicsManager();

EventManager* pEventManager = new EventManager();
std::unordered_map<EventType, std::vector<GameObject*>> eventSubscribers;

