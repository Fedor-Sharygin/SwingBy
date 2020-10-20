#pragma once

#ifndef SERIAL_H
#define SERIAL_H

#include <vector>

class GameObject;

class ObjectFactory
{
public:
	GameObject* createPlayer();
	GameObject* createBlade();
	GameObject* createShooter();
	GameObject* createBullet();
	GameObject* createSpeedBooster();
public:
private:
private:
};


class Serial
{
public:
	Serial() {};
	~Serial();

	static void LoadLevel(std::string levelPath);
public:
	static ObjectFactory* goFactory;
private:
private:
};



#endif

