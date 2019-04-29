#pragma once
#include "Component.h"
#include <string>
#include <vector>


struct KeyFrame {
	KeyFrame(float time,Transform transform) {
		this->Time = time;
		this->transform = transform;
	}
	float Time;
	Transform transform;
};


class AnimationComponent : public Component
{
public:
	AnimationComponent(std::string filename);
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
	float AnimationTime;
private:
	int currentKeyframe;
	std::vector<KeyFrame> keyFrames;
	glm::vec3 lerp(float t, const glm::vec3 a, const glm::vec3 b);
	Transform LastPos;
};
