#pragma once

#include <string>
#include <vector>
#include "Entity.h"
#include "PointLight.h"
#include "Klang/irrKlang.h"
#include "Components/BoxCollider.h"
#include "Skybox.h"
#include "Input.h"
class LevelLoader
{
public:
	LevelLoader(std::vector<Entity*>* SceneArray, std::vector<PointLight*>* LightArray, std::vector<BoxCollider*>* colliderArray, Camera* camera, Shader* modelShader, Shader* spriteShader, Shader* lightShader, Input* input, irrklang::ISoundEngine* AudioEngine,AudioComponent* FootstepSFX, Skybox* sky);
	~LevelLoader();
	void LoadLevel(std::string FileName);
private:
	std::vector<Entity*>* SceneArray;
	std::vector<PointLight*>* LightArray;
	std::vector<BoxCollider*>* colliderArray;
	Skybox* sky;
	Camera* camera;
	Shader* modelShader;
	Shader* spriteShader;
	Shader* lightShader;
	Input* input;
	irrklang::ISoundEngine* AudioEngine;
	AudioComponent* FootStepSFX;

};

