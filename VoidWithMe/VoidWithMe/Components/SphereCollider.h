#pragma once
#include "Component.h"


class SphereCollider : public Component
{
public:
	SphereCollider();
	~SphereCollider();
	void UpdateComponent(Camera* mainCamera, Transform transform) override;
};

