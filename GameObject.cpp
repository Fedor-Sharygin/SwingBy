#include "GameObject.h"
#include "Shader.h"
#include "Managers.h"

#include "Components//Component.h"
#include "Components//Shape.h"
#include "Components//Shoot.h"
#include "Components//Boost.h"
#include "Components//Physics.h"
#include "Components//Transform.h"

GameObject::GameObject()
	: del(false)
{}

GameObject const& GameObject::operator=(GameObject const& _copy)
{
	if (this == &_copy)
		return *this;

	mpComponents.clear();

	for (auto co : _copy.mpComponents)
		mpComponents.push_back(co);

	return *this;
}

GameObject::~GameObject()
{
	for (auto co : mpComponents)
		delete co;

	mpComponents.clear();
}

void GameObject::Update()
{
	for (auto co : mpComponents)
		if (co->type != TYPE_PHYSICS
			&& co->type != TYPE_BOUND_SHAPE
			&& co->type != TYPE_CONTROL)
			co->Update();

	if (type == TYPE_PLAYER)
	{
		if (sloMo == 0.3f)
		{
			if (timeInSloMo > 0.0f)
			{
				timeInSloMo -= pFrameRateManager->FrameTime();
			}
			else
			{
				timeInSloMo = 0.0f;
				sloMo = 1.0f;
			}
		}
		else
		if (sloMo == 1.0f)
		{
			if (timeInSloMo < maxTISM)
			{
				timeInSloMo += pFrameRateManager->FrameTime();
			}
			else
			{
				timeInSloMo = maxTISM;
			}
		}
//		std::cout << "Time left for slow motion: " << timeInSloMo << std::endl;
		Transform* pos = static_cast<Transform*>(getComponent(TYPE_TRANSFORM));
		Physics* phy = static_cast<Physics*>(getComponent(TYPE_PHYSICS));

		if (pos->getPosition().z >= finishDistance) {
			win = true;
		}
		else
		if (pos->getPosition().y < -pScrHeight / 8.0f - 50.0f)
		{
			del = true;
			Event* playerDed = new Event(TYPE_PLAYER_DEAD);
			pEventManager->addEvent(playerDed);
			lose = true;
		}
	}
	else
	{
		Transform* pos = static_cast<Transform*>(getComponent(TYPE_TRANSFORM));
		float cP = pCamera->camPos.z;
		float pP = pos->getPosition().z;

		if (cP - pP >= pScrWidth / 3.0f)
		{
			del = true;
		}
	}
}

Component* GameObject::getComponent(ComponentType _type)
{
	for (auto co : mpComponents)
		if (_type == co->type)
			return co;

	return nullptr;
}

void GameObject::addComponent(Component* newComp)
{
	mpComponents.push_back(newComp);
}


void GameObject::Draw(Shader _shader)
{
	Shape* _obTr = static_cast<Shape*>(getComponent(TYPE_SHAPE));

	_obTr->Draw(_shader);
}


void GameObject::HandleEvent(Event* ev)
{
	if (type == TYPE_PLAYER)
	{
		if (ev->evType == TYPE_PL_BLADE_COLL)
		{
			del = true;
			Event* playerDed = new Event(TYPE_PLAYER_DEAD);
			pEventManager->addEvent(playerDed);
			lose = true;
		}
		else
		if (ev->evType == TYPE_PL_BULLET_COLL)
			if (bulletHits > 0)
				--bulletHits;
			else
			{
				del = true;
				Event* playerDed = new Event(TYPE_PLAYER_DEAD);
				pEventManager->addEvent(playerDed);
				lose = true;
			}
		else
		if (ev->evType == TYPE_PL_BOOSTER_COLL)
		{
			GOType bt = TYPE_BOOSTER;
			auto booster = std::find_if(ev->participants.begin(), ev->participants.end(),
				[&bt](GameObject* obj) { return obj->type == bt; });
			if (booster != ev->participants.end())
			{
				Boost* b = static_cast<Boost*>((*booster)->getComponent(TYPE_BOOST));
				if (!b->triggered)
				{
					(static_cast<Physics*>(getComponent(TYPE_PHYSICS)))->speed
						+= b->speedBoost;
					b->triggered = true;
				}
			}
		}
	}
	else 
	if (type == TYPE_BULLET)
	{
		if (ev->evType == TYPE_PL_BULLET_COLL)
			del = true;
	}
	else
	if (type == TYPE_SHOOT)
	{
		if (ev->evType == TYPE_PLAYER_DEAD)
		{
			Shoot* sh = static_cast<Shoot*>(getComponent(TYPE_SHOOT));
			sh->AcquireTarget();
		}
	}
}


