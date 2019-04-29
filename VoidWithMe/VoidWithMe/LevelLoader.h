#pragma once

#include <string>
#include <vector>
#include "Entity.h"
#include "PointLight.h"
#include "Klang/irrKlang.h"
#include "Components/BoxCollider.h"
class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	void LoadLevel(std::string FileName, std::vector<Entity*>* SceneArray, std::vector<PointLight*>* LightArray, std::vector<BoxCollider*>* colliderArray, Camera* camera, Shader* modelShader, Shader* lightShader, irrklang::ISoundEngine* AudioEngine);
};

