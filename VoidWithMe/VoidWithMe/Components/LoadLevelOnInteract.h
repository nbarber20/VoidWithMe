#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "../Entity.h"
#include "../Input.h"
#include "../LevelLoader.h"
class LoadLevelOnInteract : public Component {
public:
	LoadLevelOnInteract(LevelLoader* lvlLoader, string levelToLoad,string tooltip, Entity* e, Input* i);
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
private:
	BoxCollider* collider;
	Input* input;
	string lvl;
	string tooltip;
	LevelLoader* lvlLoader;
};
