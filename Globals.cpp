#include "Globals.h"

Camera* pCamera = new Camera();
bool Debug = false;
float timeElapsed = 0.0f;
int pScrWidth = 1280;
int pScrHeight = 960;
double xpos = 0, ypos = 0;
float sloMo = 0.0f;
float timeInSloMo = 3.0f, maxTISM = 3.0f;
bool win = false;
bool lose = false;
float finishDistance = 400.0f;
std::string backgroundPath = "..//Resources//background2.jpg";
std::string instructionsPath = "..//Resources//instructions3.jpg";
std::string victoryPath = "..//Resources//win.jpg";
std::string lossPath = "..//Resources//lose.jpg";
int tripletPosition = 0;



