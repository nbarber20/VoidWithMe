#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "../Entity.h"
#include "../Input.h"
#include "AnimationComponent.h"
class PlayAnimationOnInteract : public Component {
public:
	PlayAnimationOnInteract(Entity* e, Input* i);
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
	AnimationComponent* animation;
	BoxCollider* collider;
	Input* input;
};
