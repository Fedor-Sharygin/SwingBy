#pragma once

#include "stb_image.h"
#include "unordered_map"

class Model;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Model* LoadModel(std::string texPath);
	unsigned char* LoadTexture(std::string textPath, int* width, int* height, int* nrChannels);
public:
private:
private:
	std::unordered_map<std::string, Model*> loadedModels;
	std::unordered_map<std::string, unsigned char*> loadedTextures;
};


