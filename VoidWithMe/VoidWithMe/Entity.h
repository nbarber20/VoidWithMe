#pragma once
#include "Components/Component.h"
#include "Camera.h"
#include "Transform.h"
#include "Components/MeshRenderer.h"
#include <vector>
class Entity
{
public:

	MeshRenderer* renderer;
	Transform* transform;
	

	Entity(Transform* transform, Camera* camera);
	~Entity();
	void AttachComponent(Component* c);
	void UpdateEntity();
	void Render();
private:
	std::vector<Component*> Components;
	Camera* m_mainCamera;
	GLuint m_depthTexture;
};

