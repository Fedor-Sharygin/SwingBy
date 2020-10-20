#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>

#include "Shader.h"
#include "Globals.h"
#include "GameObject.h"
#include "Serial.h"
#include "Components//Shape.h"
#include "Components//Transform.h"

using namespace glm;

float lastX = pScrWidth / 2.0f;
float lastY = pScrHeight / 2.0f;

bool firstMouse = true;

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	float deltaTime = pFrameRateManager->FrameTime() * sloMo;

	float camSpeed = 40.0f * deltaTime;

	// check if escape was pressed
	if (pInputManager->isKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
	else
	{
		if (pInputManager->isKeyPressed(GLFW_KEY_A)
			|| pInputManager->isKeyPressed(GLFW_KEY_LEFT))
			pCamera->camPos -= camSpeed * normalize(cross(pCamera->camFront, pCamera->camUp));

		if (pInputManager->isKeyPressed(GLFW_KEY_D)
			|| pInputManager->isKeyPressed(GLFW_KEY_RIGHT))
			pCamera->camPos += camSpeed * normalize(cross(pCamera->camFront, pCamera->camUp));

		if (pInputManager->isKeyTriggered(GLFW_KEY_F3))
			Debug = !Debug;

		if (pInputManager->isKeyTriggered(GLFW_KEY_TAB))
			if (sloMo != 0.0f)
				sloMo = 0.0f;
			else
				sloMo = 1.0f;
	}
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * pWindow = glfwCreateWindow(pScrWidth, pScrHeight, "IACT", NULL, NULL);
	if (NULL == pWindow)
	{
		std::cout << "Could not create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);
	glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	int width, height, nrChannels;
	unsigned int background, instructions, victory, loss;


	glGenTextures(1, &background);

	glBindTexture(GL_TEXTURE_2D, background);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(backgroundPath.c_str(), &width, &height, &nrChannels, 0);

	if (NULL != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	glGenTextures(1, &instructions);

	glBindTexture(GL_TEXTURE_2D, instructions);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	data = stbi_load(instructionsPath.c_str(), &width, &height, &nrChannels, 0);

	if (NULL != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	glGenTextures(1, &victory);

	glBindTexture(GL_TEXTURE_2D, victory);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	data = stbi_load(victoryPath.c_str(), &width, &height, &nrChannels, 0);

	if (NULL != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	glGenTextures(1, &loss);

	glBindTexture(GL_TEXTURE_2D, loss);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	data = stbi_load(lossPath.c_str(), &width, &height, &nrChannels, 0);

	if (NULL != data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	Shader* textureShader = new Shader("shaders//triangleShader.vert", "shaders//triangleShader.frag");
	Shader* colorShader = new Shader("shaders//debugShader.vert", "shaders//debugShader.frag");

	glEnable(GL_DEPTH_TEST);

	Serial::LoadLevel("..//Levels//Levels//level1.json");

	pInputManager->pWindow = pWindow;


	while (!glfwWindowShouldClose(pWindow))
	{
		pFrameRateManager->FrameStart();

		pInputManager->Update();
		processInput(pWindow);

		GameObject* isAlive = pGameObjectManager->getGO(TYPE_PLAYER);
		if (NULL != isAlive || win)
		{
			for (auto go : pGameObjectManager->mpGameObjects)
				for (auto co : go->mpComponents)
					if (co->type == TYPE_CONTROL)
						co->Update();

			pPhysicsManager->Update();
			pGameObjectManager->Update();
		}

		if (!win && !lose && sloMo == 0.0f)
		{
			pGameObjectManager->BackgroundgDraw(*textureShader, instructions, 1);
		}
		else
		{
			pGameObjectManager->BackgroundgDraw(*textureShader, background, 0);
		}

		if (!lose && !win)
		{
			pGameObjectManager->Draw(*textureShader);
			pGameObjectManager->RopeDraw(*colorShader);
			if (Debug)
			{
				pGameObjectManager->DebugDraw(*colorShader);
			}
		}
		
		if (lose)
		{
			pGameObjectManager->BackgroundgDraw(*textureShader, loss, 1);
		}

		if (win)
		{
			pGameObjectManager->BackgroundgDraw(*textureShader, victory, 1);
		}

		pGameObjectManager->FinishDraw(*colorShader);

		glfwSwapBuffers(pWindow);
		glfwPollEvents();

		pEventManager->Update();
		pGameObjectManager->DeleteObjects();

		pFrameRateManager->FrameEnd();
	}

	delete textureShader;
	delete pCamera;

	delete pFrameRateManager;
	delete pResourceManager;
	delete pInputManager;
	delete pGameObjectManager;
	delete pPhysicsManager;
	delete pCollisionManager;

	glfwTerminate();
	return 0;
}


