#pragma once


#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <unordered_map>

#include "Globals.h"


class InputManager
{
public:
	InputManager(int windowWidth = 800, int windowHeight = 600);
	~InputManager();

	void Update();

	bool isKeyPressed(unsigned int KeyScanCode);
	bool isKeyTriggered(unsigned int KeyScanCode);
	bool isKeyReleased(unsigned int KeyScanCode);

	void mouseMovement(double xPos, double yPos);
	void mouseScroll(double xoffset, double yoffset);

	void setMousePos(double xPos, double yPos);
public:
	GLFWwindow* pWindow;
private:
private:
	unsigned int keysInUse[19];

	std::unordered_map<unsigned int, bool> mCurrentKeyStates;
	std::unordered_map<unsigned int, bool> mPreviousKeyStates;

	float mouseX;
	float mouseY;

	bool mouseEntered;
};
