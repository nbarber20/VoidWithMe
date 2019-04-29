#pragma once
#include "Components/BoxCollider.h"
#include "Camera.h"
#include "Display.h"
#include <vector>
class Input
{
public:
	Input();
	void Update(float dt, Display* display,Camera* camera, std::vector<BoxCollider*> Colliders);
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float CameraSpeed = 0.001f;
	float movementSpeed = 10;
};

