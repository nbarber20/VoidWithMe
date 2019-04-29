#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "AudioComponent.h"
#include "../Entity.h"
class PlaySoundOnInteract : public Component{
public:
	PlaySoundOnInteract(Entity* e);
	void UpdateComponent( Camera* mainCamera, Transform* transform, float DeltaTime) override;
	AudioComponent* audio;
	BoxCollider* collider;
};
