#pragma once
#include "Component.h"
#include "../Entity.h"
#include "BoxCollider.h"
#include "../LevelLoader.h"
class LevelLoaderComponent : public Component
{
public:
	LevelLoaderComponent(LevelLoader* lvlLoader, string levelToLoad, Entity* e);
	~LevelLoaderComponent();
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
private:
	string m_levelToLoad;
	LevelLoader* m_LevelLoader;
	BoxCollider* collider;
};