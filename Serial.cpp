#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include <fstream>
#include <string>

#include "Serial.h"
#include "GameObject.h"
#include "Globals.h"

#include "Components//Transform.h"
#include "Components//Shape.h"
#include "Components//CircleMove.h"
#include "Components//Physics.h"
#include "Components//Control.h"
#include "Components//Shoot.h"
#include "Components//Boost.h"

using namespace glm;
using json = nlohmann::json;


GameObject* ObjectFactory::createPlayer()
{
	GameObject* playerRet;

	json player;
	std::ifstream playerDescription("..//Levels//Archetypes//Player.json");
	player = json::parse(playerDescription);

	playerRet = new GameObject();
	playerRet->type = TYPE_PLAYER;

	playerRet->bulletHits = 5;

	Transform* plPos = new Transform();
	plPos->mpOwner = playerRet;
	plPos->Serialize(player["Transform"]);
	playerRet->addComponent(plPos);

	Shape* plShape = new Shape();
	plShape->mpOwner = playerRet;
	plShape->Serialize(player["Shape"]);
	playerRet->addComponent(plShape);

	Physics* plPhysics = new Physics();
	plPhysics->mpOwner = playerRet;
//	plPhysics->Serialize(player);
	playerRet->addComponent(plPhysics);

	Control* plControl = new Control();
	plControl->mpOwner = playerRet;
	playerRet->addComponent(plControl);

	AABB* plBS = new AABB();
	plBS->mpOwner = playerRet;
	plBS->Serialize(player["AABB"]);
	glm::vec3 pos = plPos->getPosition();
	plBS->mCenter = glm::vec2(pos.z, pos.y);
	playerRet->addComponent(plBS);


	Event::Subscribe(playerRet, TYPE_PL_BLADE_COLL);
	Event::Subscribe(playerRet, TYPE_PL_BULLET_COLL);
	Event::Subscribe(playerRet, TYPE_PL_BOOSTER_COLL);


	return playerRet;
}

GameObject* ObjectFactory::createBlade()
{
	GameObject* enemyRet;

	json enemy;
	std::ifstream enemyDescription("..//Levels//Archetypes//Blade.json");
	enemy = json::parse(enemyDescription);

	enemyRet = new GameObject();
	enemyRet->type = TYPE_BLADE;

	Transform* enPos = new Transform();
	enPos->mpOwner = enemyRet;
	enPos->Serialize(enemy["Transform"]);
	enemyRet->addComponent(enPos);

	Shape* enShape = new Shape();
	enShape->mpOwner = enemyRet;
	enShape->Serialize(enemy["Shape"]);
	enemyRet->addComponent(enShape);

	CircleMove* enCM = new CircleMove();
	enCM->mpOwner = enemyRet;
	enCM->Serialize(enemy["Circling"]);
	enemyRet->addComponent(enCM);

	Line* enBS = new Line();
	enBS->mpOwner = enemyRet;
	enBS->Serialize(enemy["Line"]);
	glm::vec3 pos = enPos->getPosition();
	enBS->start = glm::vec2(pos.z, pos.y);
	enemyRet->addComponent(enBS);


	Event::Subscribe(enemyRet, TYPE_PL_BLADE_COLL);


	return enemyRet;
}

GameObject* ObjectFactory::createShooter()
{
	GameObject* enemyRet;

	json enemy;
	std::ifstream enemyDescription("..//Levels//Archetypes//Shooter.json");
	enemy = json::parse(enemyDescription);

	enemyRet = new GameObject();
	enemyRet->type = TYPE_SHOOTER;

	Transform* enPos = new Transform();
	enPos->mpOwner = enemyRet;
	enPos->Serialize(enemy["Transform"]);
	enemyRet->addComponent(enPos);

	Shape* enShape = new Shape();
	enShape->mpOwner = enemyRet;
	enShape->Serialize(enemy["Shape"]);
	enemyRet->addComponent(enShape);

	Shoot* enShoot = new Shoot();
	enShoot->mpOwner = enemyRet;
	enShoot->Serialize(enemy["Shooter"]);
	enemyRet->addComponent(enShoot);


	Event::Subscribe(enemyRet, TYPE_PLAYER_DEAD);


	return enemyRet;
}

GameObject* ObjectFactory::createBullet()
{
	GameObject* bullRet;

	json bullet;
	std::ifstream bulletDescription("..//Levels//Archetypes//Bullet.json");
	bullet = json::parse(bulletDescription);

	bullRet = new GameObject();
	bullRet->type = TYPE_BULLET;
	
	Transform* buPos = new Transform();
	buPos->mpOwner = bullRet;
	buPos->Serialize(bullet["Transform"]);
	bullRet->addComponent(buPos);

	Shape* buShape = new Shape();
	buShape->mpOwner = bullRet;
	buShape->Serialize(bullet["Shape"]);
	bullRet->addComponent(buShape);

	AABB* buBS = new AABB();
	buBS->mpOwner = bullRet;
	buBS->Serialize(bullet["AABB"]);
	glm::vec3 pos = buPos->getPosition();
	buBS->mCenter += glm::vec2(pos.z, pos.y);
	bullRet->addComponent(buBS);

	Physics* buPhysics = new Physics();
	buPhysics->mpOwner = bullRet;
	buPhysics->gravity = glm::vec3(0.0f);
	bullRet->addComponent(buPhysics);


	Event::Subscribe(bullRet, TYPE_PL_BULLET_COLL);


	return bullRet;
}

GameObject* ObjectFactory::createSpeedBooster()
{
	GameObject* boostRet;

	json booster;
	std::ifstream boosterDescription("..//Levels//Archetypes//Booster.json");
	booster = json::parse(boosterDescription);

	boostRet = new GameObject();
	boostRet->type = TYPE_BOOSTER;

	Transform* boPos = new Transform();
	boPos->mpOwner = boostRet;
	boPos->Serialize(booster["Transform"]);
	boostRet->addComponent(boPos);

	Shape* boShape = new Shape();
	boShape->mpOwner = boostRet;
	boShape->Serialize(booster["Shape"]);
	boostRet->addComponent(boShape);

	AABB* boBS = new AABB();
	boBS->mpOwner = boostRet;
	boBS->Serialize(booster["AABB"]);
	glm::vec3 pos = boPos->getPosition();
	boBS->mCenter = glm::vec2(pos.z, pos.y);
	boostRet->addComponent(boBS);

	Boost* boB = new Boost();
	boB->mpOwner = boostRet;
	boB->Serialize(booster["Boost"]);
	boostRet->addComponent(boB);


	Event::Subscribe(boostRet, TYPE_PL_BOOSTER_COLL);


	return boostRet;
}


ObjectFactory* Serial::goFactory = new ObjectFactory();

Serial::~Serial()
{
	delete goFactory;
}

void Serial::LoadLevel(std::string levelPath)
{
	json level;
	std::ifstream levelDescription(levelPath);
	level = json::parse(levelDescription);

	auto fd = level.find("Finish Line");
	if (fd != level.end())
	{
		finishDistance = level["Finish Line"].get<float>();
	}

	auto pl = level.find("Player");
	if (pl != level.end())
	{
		GameObject* player = goFactory->createPlayer();
		
		auto tran = level["Player"].find("Transform");
		if (tran != level["Player"].end())
			player->getComponent(TYPE_TRANSFORM)->Serialize(level["Player"]["Transform"]);

		auto sh = level["Player"].find("Shape");
		if (sh != level["Player"].end())
			player->getComponent(TYPE_SHAPE)->Serialize(level["Player"]["Shape"]);

		auto ab = level["Player"].find("AABB");
		if (ab != level["Player"].end())
			player->getComponent(TYPE_BOUND_SHAPE)->Serialize(level["Player"]["AABB"]);

		Transform* plPos = static_cast<Transform*>(player->getComponent(TYPE_TRANSFORM));
		AABB* plHB = static_cast<AABB*>(player->getComponent(TYPE_BOUND_SHAPE));
		plHB->mCenter += glm::vec2(plPos->getPosition().z, plPos->getPosition().y)
			+ glm::vec2(0.0f, plPos->getPosition().y * 0.375f);

		pGameObjectManager->addGameObject(player);
	}

	// A LEVEL CAN'T HAVE MORE THAN 10 OF EACH NON-PLAYER GAME OBJECT TYPE

	for (int i = 1; i <= 10; ++i)
	{
		std::string blName = "Blade_", shName = "Shooter_", boName = "Booster_";
		blName = blName + std::to_string(i);
		shName = shName + std::to_string(i);
		boName = boName + std::to_string(i);

		auto bla = level.find(blName);
		auto sho = level.find(shName);
		auto boo = level.find(boName);

		if (bla != level.end())
		{
			GameObject* blade = goFactory->createBlade();

			auto tran = level[blName].find("Transform");
			if (tran != level[blName].end())
				blade->getComponent(TYPE_TRANSFORM)->Serialize(level[blName]["Transform"]);

			auto sh = level[blName].find("Shape");
			if (sh != level[blName].end())
				blade->getComponent(TYPE_SHAPE)->Serialize(level[blName]["Shape"]);

			auto ab = level[blName].find("Line");
			if (ab != level[blName].end())
				blade->getComponent(TYPE_BOUND_SHAPE)->Serialize(level[blName]["Line"]);

			Transform* blPos = static_cast<Transform*>(blade->getComponent(TYPE_TRANSFORM));
			Line* blHB = static_cast<Line*>(blade->getComponent(TYPE_BOUND_SHAPE));
			blHB->start += glm::vec2(blPos->getPosition().z, blPos->getPosition().y);

			auto ci = level[blName].find("Circling");
			if (ci != level[blName].end())
				blade->getComponent(TYPE_CIRCLE_MOVE)->Serialize(level[blName]["Circling"]);

			bool isThisBl2 = !blName.compare("Blade_2");
			pGameObjectManager->addGameObject(blade);
		}

		if (sho != level.end())
		{
			GameObject* shooter = goFactory->createShooter();

			auto tran = level[shName].find("Transform");
			if (tran != level[shName].end())
				shooter->getComponent(TYPE_TRANSFORM)->Serialize(level[shName]["Transform"]);

			auto sh = level[shName].find("Shape");
			if (sh != level[shName].end())
				shooter->getComponent(TYPE_SHAPE)->Serialize(level[shName]["Shape"]);

			auto shot = level[shName].find("Shooter");
			if (shot != level[shName].end())
				shooter->getComponent(TYPE_SHOOT)->Serialize(level[shName]["Circling"]);

			pGameObjectManager->addGameObject(shooter);
		}

		if (boo != level.end())
		{
			GameObject* booster = goFactory->createSpeedBooster();

			auto tran = level[boName].find("Transform");
			if (tran != level[boName].end())
				booster->getComponent(TYPE_TRANSFORM)->Serialize(level[boName]["Transform"]);

			auto sh = level[boName].find("Shape");
			if (sh != level[boName].end())
				booster->getComponent(TYPE_SHAPE)->Serialize(level[boName]["Shape"]);

			auto ab = level[boName].find("AABB");
			if (ab != level[boName].end())
				booster->getComponent(TYPE_BOUND_SHAPE)->Serialize(level[boName]["AABB"]);

			Transform* boPos = static_cast<Transform*>(booster->getComponent(TYPE_TRANSFORM));
			AABB* boHB = static_cast<AABB*>(booster->getComponent(TYPE_BOUND_SHAPE));
			boHB->mCenter += glm::vec2(boPos->getPosition().z, boPos->getPosition().y);

			auto bo = level[boName].find("Boost");
			if (ab != level[boName].end())
				booster->getComponent(TYPE_BOOST)->Serialize(level[boName]["Boost"]);

			pGameObjectManager->addGameObject(booster);
		}
	}
}


