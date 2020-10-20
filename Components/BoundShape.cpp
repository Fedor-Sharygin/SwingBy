#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "BoundShape.h"
#include "Transform.h"
#include "Physics.h"

#include "..//GameObject.h"
#include "..//Shader.h"
#include "..//Globals.h"


void AABB::Update()
{
	Physics* goPh = static_cast<Physics*>(mpOwner->getComponent(TYPE_PHYSICS));
	glm::vec3 movement;

	if (nullptr != goPh)
		movement = goPh->speed * pFrameRateManager->FrameTime() * sloMo;
	else
		movement = glm::vec3(0.0f);

	mCenter += glm::vec2(movement.z, movement.y);
}

void AABB::Serialize(json& j)
{
	Transform* _goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));

	auto mc = j.find("center");
	if (mc != j.end())
		mCenter = glm::vec2(j["center"][0].get<float>(),
					j["center"][1].get<float>());

	auto w = j.find("width");
	if (w != j.end())
	{
		width = j["width"].get<float>();
		width *= _goTr->getSize().z;
	}
	auto h = j.find("height");
	if (h != j.end())
	{
		height = j["height"].get<float>();
		height *= _goTr->getSize().y;
	}
}

void AABB::Draw(Shader _s)
{
	float vertices[] = {
		-30.0f, -height / 2.0f, +width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-30.0f, -height / 2.0f, -width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f,
											
		-30.0f, -height / 2.0f, -width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-30.0f, +height / 2.0f, -width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f,
								
		-30.0f, +height / 2.0f, -width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-30.0f, +height / 2.0f, +width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f,
									
		-30.0f, +height / 2.0f, +width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-30.0f, -height / 2.0f, +width / 2.0f,	0.0f, 1.0f, 0.0f, 1.0f
	};
	
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 view = glm::lookAt(pCamera->camPos, pCamera->camPos + pCamera->camFront, pCamera->camUp);

	glm::mat4 projection = glm::ortho(-pScrWidth / 8.0f, pScrWidth / 8.0f,
		-pScrHeight / 8.0f, pScrHeight / 8.0f,
		0.1f, 3000.0f);

	_s.use();
	  
	_s.setMat4("view", view);
	_s.setMat4("projection", projection);

	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, mCenter.y, mCenter.x));

	_s.setMat4("model", model);

	glDrawArrays(GL_LINES, 0, 8);

	_s.unuse();
}


void Line::Update()
{
	Transform* goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));
	Physics* goPh = static_cast<Physics*>(mpOwner->getComponent(TYPE_PHYSICS));
	glm::vec3 movement;

	if (nullptr != goPh)
		movement = goPh->speed * pFrameRateManager->FrameTime() * sloMo;
	else
		movement = glm::vec3(0.0f);

	start += glm::vec2(movement.z, movement.y);
	tilt = origTilt + goTr->getTilt();
}

void Line::Serialize(json& j)
{
	Transform* _goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));

	auto st = j.find("start");
	if (st != j.end())
		start = glm::vec2(j["start"][0].get<float>(),
						  j["start"][1].get<float>())
			+ glm::vec2(_goTr->getPosition().z, _goTr->getPosition().y);

	auto l = j.find("length");
	if (l != j.end())
	{
		length = j["length"].get<float>();
		length *= _goTr->getSize().z;
	}
	auto t = j.find("tilt");
	tilt = 0;
	if (t != j.end())
		origTilt = j["tilt"].get<float>();
}

void Line::Draw(Shader _s)
{
	float vertices[] = {
		-30.0f, 0.0f,   0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		-30.0f, length, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 view = glm::lookAt(pCamera->camPos, pCamera->camPos + pCamera->camFront, pCamera->camUp);

	glm::mat4 projection = glm::ortho(-pScrWidth / 8.0f, pScrWidth / 8.0f,
		-pScrHeight / 8.0f, pScrHeight / 8.0f,
		0.1f, 3000.0f);

	_s.use();

	_s.setMat4("view", view);
	_s.setMat4("projection", projection);

	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, start.y, start.x));
	model = glm::rotate(model, glm::radians(tilt), glm::vec3(1.0f, 0.0f, 0.0f));

	_s.setMat4("model", model);

	glDrawArrays(GL_LINES, 0, 2);

	_s.unuse();
}


