#pragma once

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <glm/glm.hpp>

#include "Camera.h"
#include "Managers.h"

using namespace glm;

extern Camera* pCamera;
extern bool Debug;
extern float timeElapsed;
extern int pScrWidth;
extern int pScrHeight;
extern double xpos, ypos;
extern float sloMo;
extern float timeInSloMo, maxTISM;
extern bool win;
extern bool lose;
extern float finishDistance;
extern std::string backgroundPath;
extern std::string instructionsPath;
extern std::string victoryPath;
extern std::string lossPath;
extern int tripletPosition;


#endif

