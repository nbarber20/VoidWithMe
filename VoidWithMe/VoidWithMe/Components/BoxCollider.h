#pragma once
#include "Component.h"
#include "../Entity.h"



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
	BoxCollider(Entity* e, glm::vec3 Offset, glm::vec3 Scale, bool Trigger);
	~BoxCollider();
	void UpdateComponent( Camera* mainCamera, Transform* transform, float DeltaTime) override;
	bool PointOverlap(glm::vec3 Origin);
	bool Overlap(glm::vec3 Origin, float OriginScale);
	void Draw();

	bool isTrigger;
	bool isOverlapping = false;

	AABB boundingBox;
	glm::vec3 Scale;
	glm::vec3 Offset;
};

