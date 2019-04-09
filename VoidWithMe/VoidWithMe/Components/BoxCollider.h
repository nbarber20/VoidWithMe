#pragma once
#include "Component.h"




struct AABB {
public:
	AABB(const glm::vec3& Min = glm::vec3(), const glm::vec3& Max = glm::vec3()) {
		this->Min = Min;
		this->Max = Max;
	}

	inline glm::vec3* GetMin() { return &Min; }
	inline glm::vec3* GetMax() { return &Max; }

private:
	glm::vec3 Min;
	glm::vec3 Max;
};





class BoxCollider : public Component
{
public:
	BoxCollider(glm::vec3 Offset, glm::vec3 Scale);
	~BoxCollider();
	void UpdateComponent(Camera* mainCamera, Transform transform) override;
	bool PointOverlap(glm::vec3 Origin);
	void Draw();

	AABB boundingBox;
	glm::vec3 Scale;
};

