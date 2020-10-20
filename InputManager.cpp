#include "InputManager.h"


InputManager::InputManager(int windowWidth, int windowHeight)
	:
	mouseX(float(windowWidth) / 2.0f), mouseY(float(windowHeight) / 2.0f),
	mouseEntered(false)
{
	keysInUse[0] = GLFW_KEY_W;
	keysInUse[1] = GLFW_KEY_A;
	keysInUse[2] = GLFW_KEY_S;
	keysInUse[3] = GLFW_KEY_D;

	keysInUse[4] = GLFW_KEY_UP;
	keysInUse[5] = GLFW_KEY_LEFT;
	keysInUse[6] = GLFW_KEY_DOWN;
	keysInUse[7] = GLFW_KEY_RIGHT;

	keysInUse[8] = GLFW_KEY_1;
	keysInUse[9] = GLFW_KEY_2;
	keysInUse[10] = GLFW_KEY_3;
	keysInUse[11] = GLFW_KEY_4;

	keysInUse[12] = GLFW_KEY_LEFT_SHIFT;

	keysInUse[13] = GLFW_KEY_LEFT_CONTROL;

	keysInUse[14] = GLFW_KEY_SPACE;

	keysInUse[15] = GLFW_KEY_ESCAPE;

	keysInUse[16] = GLFW_MOUSE_BUTTON_LEFT;

	keysInUse[17] = GLFW_KEY_F3;

	keysInUse[18] = GLFW_KEY_TAB;

	for (auto key : keysInUse)
	{
		mCurrentKeyStates.insert(std::make_pair(key, false));
		mPreviousKeyStates.insert(std::make_pair(key, false));
	}
}

InputManager::~InputManager()
{
	mCurrentKeyStates.clear();
	mPreviousKeyStates.clear();
}

void InputManager::Update()
{
	mPreviousKeyStates = mCurrentKeyStates;

	for (auto key : keysInUse)
	{
//		std::cout << mPreviousKeyStates[key] << std::endl;
		mCurrentKeyStates[key] = (glfwGetKey(pWindow, key) == GLFW_PRESS);
//		std::cout << mCurrentKeyStates[key] << std::endl << std::endl;
	}
//	std::cout << std::endl << std::endl;

	mCurrentKeyStates[GLFW_MOUSE_BUTTON_LEFT]
		= (glfwGetMouseButton(pWindow, GLFW_MOUSE_BUTTON_LEFT)== GLFW_PRESS);

	glfwGetCursorPos(pWindow, &xpos, &ypos);
}

bool InputManager::isKeyPressed(unsigned int KeyScanCode)
{
//	if (mCurrentKeyStates[KeyScanCode])
//		std::cout << KeyScanCode << " key pressed" << std::endl;

	return mCurrentKeyStates[KeyScanCode];
}

bool InputManager::isKeyTriggered(unsigned int KeyScanCode)
{
//	if (!mPreviousKeyStates[KeyScanCode] && mCurrentKeyStates[KeyScanCode])
//		std::cout << KeyScanCode << " key triggered" << std::endl;

	return (!mPreviousKeyStates[KeyScanCode] && mCurrentKeyStates[KeyScanCode]);
}

bool InputManager::isKeyReleased(unsigned int KeyScanCode)
{
//	if (mPreviousKeyStates[KeyScanCode] && !mCurrentKeyStates[KeyScanCode])
//		std::cout << KeyScanCode << " key released" << std::endl;

	return (mPreviousKeyStates[KeyScanCode] && !mCurrentKeyStates[KeyScanCode]);
}

void InputManager::mouseMovement(double xPos, double yPos)
{
	if (!mouseEntered)
	{
		mouseX = xPos;
		mouseY = yPos;
		mouseEntered = true;
	}

	float deltaX = xPos - mouseX;
	float deltaY = yPos - mouseY;
	mouseX = xPos;
	mouseY = yPos;
	float sensitivity = 0.05f;

	deltaX *= sensitivity;
	deltaY *= sensitivity;

	pCamera->spin += deltaX;
	pCamera->tilt -= deltaY;

	if (pCamera->tilt > 89.0f)
		pCamera->tilt = 89.0f;
	if (pCamera->tilt < -89.0f)
		pCamera->tilt = -89.0f;


	if (pCamera->spin > 180.0f)
		pCamera->spin -= 360.0f;
	if (pCamera->spin < -180.0f)
		pCamera->spin += 360.0f;

	vec3 front;
	front.x = cos(radians(pCamera->tilt)) * cos(radians(pCamera->spin));
	front.y = sin(radians(pCamera->tilt));
	front.z = cos(radians(pCamera->tilt)) * sin(radians(pCamera->spin));
	pCamera->camFront = normalize(front);
}

void InputManager::mouseScroll(double xoffset, double yoffset)
{
	if (pCamera->zoom >= 1.0f && pCamera->zoom <= 45.0f)
		pCamera->zoom -= yoffset;
	if (pCamera->zoom <= 1.0f)
		pCamera->zoom = 1.0f;
	if (pCamera->zoom >= 45.0f)
		pCamera->zoom = 45.0f;
}

void InputManager::setMousePos(double xPos, double yPos)
{
	glfwSetCursorPos(pWindow, xPos, yPos);
	xpos = xPos;
	ypos = yPos;
}


