#include "Control.h"
#include "Transform.h"
#include "Physics.h"
#include "..//GameObject.h"
#include "..//Globals.h"


void Control::Update()
{
	if (pInputManager->isKeyTriggered(GLFW_MOUSE_BUTTON_LEFT))
	{
		Physics* goPh = static_cast<Physics*>(mpOwner->getComponent(TYPE_PHYSICS));
		goPh->setGrapplePoint();
	}
	else
	if (pInputManager->isKeyReleased(GLFW_MOUSE_BUTTON_LEFT))
	{
		Physics* goPh = static_cast<Physics*>(mpOwner->getComponent(TYPE_PHYSICS));
		goPh->grappled = false;
	}
	else
	if (pInputManager->isKeyTriggered(GLFW_KEY_SPACE))
	{
		if (sloMo == 1.0f)
			sloMo = 0.3f;
		else
		if (sloMo == 0.3f)
			sloMo = 1.0f;
	}
}


