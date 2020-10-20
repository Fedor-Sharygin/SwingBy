#include "Globals.h"
#include "EventManager.h"


void Event::Subscribe(GameObject* _ns, EventType _type)
{
	auto it = std::find(eventSubscribers[_type].begin(), eventSubscribers[_type].end(), _ns);

	if (it == eventSubscribers[_type].end())
		eventSubscribers[_type].push_back(_ns);
}

void Event::unSubscribe(GameObject* _ns, EventType _type)
{
	auto it = std::find(eventSubscribers[_type].begin(), eventSubscribers[_type].end(), _ns);

	if (it != eventSubscribers[_type].end())
		eventSubscribers[_type].erase(it);
}


EventManager::~EventManager()
{
	for (auto ev : events)
		delete ev;

	events.clear();
}

void EventManager::Update()
{
	for (auto ev : events)
	{
		pGameObjectManager->HandleEvent(ev);
		delete ev;
	}

	events.clear();
}


