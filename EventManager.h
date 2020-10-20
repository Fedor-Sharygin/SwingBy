#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <unordered_map>

enum EventType
{
	TYPE_PL_BLADE_COLL = 0,
	TYPE_PL_BULLET_COLL,
	TYPE_PL_BOOSTER_COLL,
	TYPE_PLAYER_DEAD
};

class GameObject;

class Event
{
public:
	Event(EventType _t) : evType(_t) {}
	~Event() {}

	static void Subscribe(GameObject* _ns, EventType _type);
	static void unSubscribe(GameObject* _ns, EventType _type);
public:
	EventType evType;
	std::vector<GameObject*> participants;
private:
private:
};



class EventManager
{
public:
	EventManager() : events() {};
	~EventManager();

	void addEvent(Event* ev)
	{ events.push_back(ev); };

	void Update();
public:
private:
private:
	std::vector<Event*> events;
};




#endif

