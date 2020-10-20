#include "Physics.h"
#include "Transform.h"

#include "..//GameObject.h"
#include "..//Globals.h"
#include "..//Shader.h"

void Physics::Update()
{
	Transform* _goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));
	_goTr->lastPos = _goTr->getPosition();
	_goTr->setPosition(_goTr->getPosition() + speed * pFrameRateManager->FrameTime() * sloMo);

	if (grappled)
	{
		glm::vec3 dist = grapplePoint - _goTr->getPosition();

		float sqD = glm::dot(dist, dist);
		glm::vec3 pullNorm = glm::normalize(dist);

		if (sqD < sqDistance)
			pullForce = glm::vec3(0.0f);
		else
		if (sqD == sqDistance)
			pullForce = 100.0f * pullNorm;
		else
		{
			float coef = sqD / sqDistance * 1.25f;
			pullForce = coef * 100.0f * pullNorm;
		}

		glm::vec2 topp = glm::vec2(pCamera->camPos.z - pScrWidth / 8.0f, pScrHeight / 8.0f);
		glm::vec2 grRelPos = 4.0f * glm::vec2(grapplePoint.z - topp.x, topp.y - grapplePoint.y);

		pInputManager->setMousePos(grRelPos.x, grRelPos.y);
	}
	else
	{
		pullForce = glm::vec3(0.0f);
	}

	allForces = mass * gravity + pullForce;
	allForces *= 1.5f;

	speed += allForces / mass * pFrameRateManager->FrameTime() * sloMo;
}

void Physics::setGrapplePoint()
{
	grapplePoint = glm::vec3(0.0f, pScrHeight / 8.0f - ypos / 4.0f + pCamera->camPos.y,
		-pScrWidth / 8.0f + xpos / 4.0f + pCamera->camPos.z);

	Transform* goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));

	glm::vec3 dist = grapplePoint - goTr->getPosition();
	sqDistance = glm::dot(dist, dist);

	grappled = true;
}

void Physics::Draw(Shader _s)
{
	Transform* _goTr = static_cast<Transform*>(mpOwner->getComponent(TYPE_TRANSFORM));
	glm::vec2 dist = glm::vec2(grapplePoint.z, grapplePoint.y) - 
		glm::vec2(_goTr->getPosition().z, _goTr->getPosition().y);
	float length = glm::length(dist);

	float vertices[] = {
		0.0f, 0.0f,   0.0f,	0.588f, 0.294f, 0.0f, 1.0f,
		0.0f, length, 0.0f,	0.588f, 0.294f, 0.0f, 1.0f
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

	float PI = 3.14159265359;

	float tilt = PI / 2.0f - acosf(glm::normalize(dist).x);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, _goTr->getPosition());
	model = glm::rotate(model, tilt, glm::vec3(1.0f, 0.0f, 0.0f));

	_s.setMat4("model", model);

	glDrawArrays(GL_LINES, 0, 2);

	_s.unuse();
}


