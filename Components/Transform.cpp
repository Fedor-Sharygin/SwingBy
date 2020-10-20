#include "Transform.h"

#include "..//Globals.h"
#include "..//GameObject.h"


Transform::Transform() : Component(TYPE_TRANSFORM),
	position(vec3(0.0f)), lastPos(vec3(0.0f)),
	scaleSize(vec3(1.0f)), tilt(0.0f), spin(0.0f), yaw(0.0f)
{}

Transform::~Transform()
{}

void Transform::Update()
{
//	if (tilt > 10000)
//		position += vec3(0.0f, 200.0f, 200.0f) * pFrameRateManager->FrameTime() * sloMo;

	glm::vec3 posDifference = position - lastPos;

	if (mpOwner->type == TYPE_PLAYER)
	{
		pCamera->camPos.z += posDifference.z;
	}
}


void Transform::Serialize(json& j)
{
	auto p = j.find("Position");
	if (p != j.end())
		setPosition(vec3(j["Position"][0].get<float>(),
			j["Position"][1].get<float>(),
			j["Position"][2].get<float>()));

	lastPos = getPosition();

	auto s = j.find("Size");
	if (s != j.end())
		setSize(vec3(j["Size"][0].get<float>(),
			j["Size"][1].get<float>(),
			j["Size"][2].get<float>()));

	auto sp = j.find("Spin");
	if (sp != j.end())
		setSpin(j["Spin"].get<float>());
	auto ti = j.find("Tilt");
	if (ti != j.end())
		setTilt(j["Tilt"].get<float>());
	auto ya = j.find("Yaw");
	if (ya != j.end())
		setYaw(j["Yaw"].get<float>());
}
