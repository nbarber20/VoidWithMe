#pragma once
#include "Components/BoxCollider.h"
#include "Components/AudioComponent.h"
#include "Camera.h"
#include "Display.h"
#include "Common/text2D.hpp"
#include <vector>
class Input
{
public:
	Input(TextRenderer* text, AudioComponent* FootSfx);
	void Update(float dt, Display* display,Camera* camera, std::vector<BoxCollider*> Colliders);
	bool Interacting = false;
	void ShowText();
	void ShowText(string text);
private:
	TextRenderer* Text;
	AudioComponent* FootStepSFX;
	int ScreenWidth;
	int ScreenHeight;
	float horizontalAngle = 1.57f;
	float verticalAngle = 0.0f;
	float CameraSpeed = 0.001f;
	float movementSpeed = 10;
};

