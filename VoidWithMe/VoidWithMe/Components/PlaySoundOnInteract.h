#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "AudioComponent.h"
#include "../Entity.h"
#include "../Input.h"
class PlaySoundOnInteract : public Component{
public:
	PlaySoundOnInteract(Entity* e, Input* i);
	void UpdateComponent( Camera* mainCamera, Transform* transform, float DeltaTime) override;
	AudioComponent* audio;
	BoxCollider* collider;
	Input* input;
};
