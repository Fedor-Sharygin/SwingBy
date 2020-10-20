#include "Components//Model.h"
#include "ResourceManager.h"
/////// REDO THIS!!!!!!!!!!!

ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{
	for (auto _lm : loadedModels)
		delete _lm.second;

	for (auto _lm : loadedTextures)
		delete _lm.second;

	loadedModels.clear();
	loadedTextures.clear();
}


Model* ResourceManager::LoadModel(std::string texPath)
{
	Model* dataMod = loadedModels[texPath];

	if (nullptr != dataMod)
		return dataMod;

	dataMod = new Model(texPath);

	if (nullptr != dataMod)
		loadedModels[texPath] = dataMod;

	return dataMod;
}


unsigned char* ResourceManager::LoadTexture(std::string textPath, int* width, int* height, int* nrChannels)
{
	unsigned char* dataMod = loadedTextures[textPath];

	if (nullptr != dataMod)
		return dataMod;

	dataMod = stbi_load(textPath.c_str(), width, height, nrChannels, 0);

	if (nullptr != dataMod)
		loadedTextures[textPath] = dataMod;

	return dataMod;
}


