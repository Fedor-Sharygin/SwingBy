#include "GameObjectManager.h"
#include "GameObject.h"
#include "Managers.h"
#include "Components//Transform.h"
#include "Components//Sprite.h"
#include "Components//Physics.h"


GameObjectManager::GameObjectManager() {}

GameObject* GameObjectManager::getGO(GOType _t)
{
	for (auto go : mpGameObjects)
		if (go->type == _t)
			return go;

	return NULL;
}

GameObjectManager::~GameObjectManager()
{
	for (auto go : mpGameObjects)
		delete go;

	mpGameObjects.clear();
}

void GameObjectManager::addGameObject(GameObject* _go)
{
	mpGameObjects.push_back(_go);
}

void GameObjectManager::Update()
{
	if (win)
		std::cout << "YOU WON!!!" << std::endl;
	else
		for (auto go : mpGameObjects)
			go->Update();
}

void GameObjectManager::Draw(Shader _shader)
{
	for (auto go : mpGameObjects)
		if (NULL != go->getComponent(TYPE_SHAPE))
		{
			Transform* goTr = static_cast<Transform*>(go->getComponent(TYPE_TRANSFORM));
			if (abs(goTr->getPosition().z - pCamera->camPos.z) < pScrWidth / 4.0f)
				go->Draw(_shader);
		}
}

void GameObjectManager::HandleEvent(Event* ev)
{
	for (auto go : mpGameObjects)
	{
		if (eventSubscribers[ev->evType].empty())
			go->HandleEvent(ev);
		else
		{
			auto subbed = std::find(eventSubscribers[ev->evType].begin(),
				eventSubscribers[ev->evType].end(), go);
			auto parted = std::find(ev->participants.begin(),
				ev->participants.end(), go);
	
			if (subbed != eventSubscribers[ev->evType].end()
				&& parted != ev->participants.end())
				go->HandleEvent(ev);
		}
	}
}

void GameObjectManager::DeleteObjects()
{
	auto it = mpGameObjects.begin();

	while (it != mpGameObjects.end())
		if ((*it)->del)
		{
			Event::unSubscribe(*it, TYPE_PL_BLADE_COLL);
			Event::unSubscribe(*it, TYPE_PL_BULLET_COLL);
			it = mpGameObjects.erase(it);
		}
		else
			++it;
}


void GameObjectManager::DebugDraw(Shader _shader)
{
	for (auto go : mpGameObjects)
	{
		BoundShape* goBS = static_cast<BoundShape*>(go->getComponent(TYPE_BOUND_SHAPE));
		if (NULL != goBS)
			goBS->Draw(_shader);
	}
}

void GameObjectManager::BackgroundgDraw(Shader _shader, unsigned int texture, bool front)
{
	_shader.use();

	if (pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f < pCamera->camPos.z) ++tripletPosition;
	else
	if (-pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f > pCamera->camPos.z) --tripletPosition;

	float vertices[] = {
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition - 1) * pScrWidth / 4.0f,	0.0f, 0.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition - 1) * pScrWidth / 4.0f,	0.0f, 1.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition - 1) * pScrWidth / 4.0f,	1.0f, 1.0f,
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition - 1) * pScrWidth / 4.0f,	0.0f, 0.0f,
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition - 1) * pScrWidth / 4.0f,	1.0f, 0.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition - 1) * pScrWidth / 4.0f,	1.0f, 1.0f,
																			 
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f,	0.0f, 0.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f,	0.0f, 1.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f,	1.0f, 1.0f,
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f,	0.0f, 0.0f,
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f,	1.0f, 0.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition) * pScrWidth / 4.0f,	1.0f, 1.0f,
												 							 
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition + 1) * pScrWidth / 4.0f,	0.0f, 0.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition + 1) * pScrWidth / 4.0f,	0.0f, 1.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition + 1) * pScrWidth / 4.0f,	1.0f, 1.0f,
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f, -pScrWidth / 8.0f + float(tripletPosition + 1) * pScrWidth / 4.0f,	0.0f, 0.0f,
		glm::pow(-1, front) * 50.0f, -pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition + 1) * pScrWidth / 4.0f,	1.0f, 0.0f,
		glm::pow(-1, front) * 50.0f,  pScrHeight / 8.0f,  pScrWidth / 8.0f + float(tripletPosition + 1) * pScrWidth / 4.0f,	1.0f, 1.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shader.setInt("texture_diffuse1", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	mat4 view = lookAt(pCamera->camPos, pCamera->camPos + pCamera->camFront, pCamera->camUp);

	mat4 projection = ortho(-pScrWidth / 8.0f, pScrWidth / 8.0f,
		-pScrHeight / 8.0f, pScrHeight / 8.0f,
		0.1f, 3000.0f);

	_shader.setMat4("view", view);
	_shader.setMat4("projection", projection);

	glBindVertexArray(VAO);

	mat4 model = mat4(1.0f);
	model = translate(model, glm::vec3(0.0f));
	_shader.setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, 18);

	_shader.unuse();
}

void GameObjectManager::RopeDraw(Shader _shader)
{
	for (auto go : mpGameObjects)
	{
		Physics* goPh = static_cast<Physics*>(go->getComponent(TYPE_PHYSICS));
		if (NULL != goPh)
			if (goPh->grappled)
				goPh->Draw(_shader);
	}
}


void GameObjectManager::FinishDraw(Shader _shader)
{
	FSDraw(_shader, 0.0f);
	FSDraw(_shader, 1.0f);
}

void GameObjectManager::FSDraw(Shader _shader, float color)
{
	if (abs(finishDistance - pCamera->camPos.z) < pScrWidth / 3.0f)
	{
		int c = color;

		float Square[] = {
			15.0f, -5.0f, -5.0f,	color, color, color, 1.0f,
			15.0f,  5.0f, -5.0f,	color, color, color, 1.0f,
			15.0f,  5.0f,  5.0f,	color, color, color, 1.0f,
			15.0f, -5.0f, -5.0f,	color, color, color, 1.0f,
			15.0f, -5.0f,  5.0f,	color, color, color, 1.0f,
			15.0f,  5.0f,  5.0f,	color, color, color, 1.0f
		};

		glm::vec3 SqPos[] = {
			glm::vec3(0.0f,  15.0f, finishDistance - glm::pow(-1, c) * 5.0f),
			glm::vec3(0.0f,   5.0f, finishDistance + glm::pow(-1, c) * 5.0f),
			glm::vec3(0.0f,  -5.0f, finishDistance - glm::pow(-1, c) * 5.0f),
			glm::vec3(0.0f, -15.0f, finishDistance + glm::pow(-1, c) * 5.0f)
		};

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Square), Square, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		_shader.use();

		mat4 view = lookAt(pCamera->camPos, pCamera->camPos + pCamera->camFront, pCamera->camUp);

		mat4 projection = ortho(-pScrWidth / 8.0f, pScrWidth / 8.0f,
			-pScrHeight / 8.0f, pScrHeight / 8.0f,
			0.1f, 3000.0f);

		_shader.setMat4("view", view);
		_shader.setMat4("projection", projection);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, SqPos[i]);
			_shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		_shader.unuse();
	}
}


