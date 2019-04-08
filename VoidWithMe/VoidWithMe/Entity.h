#pragma once
#include "Components/Component.h"
#include "Camera.h"
#include "Transform.h"
#include <vector>
class Entity
{
public:
	Entity(Transform transform, Camera* camera, GLuint depthTexture);
	~Entity();
	void AttachComponent(Component* c);
	void UpdateEntity();
private:
	std::vector<Component*> Components;
	Transform m_transform;
	Camera* m_mainCamera;
	GLuint m_depthTexture;
};

