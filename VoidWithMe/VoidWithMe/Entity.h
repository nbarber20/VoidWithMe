#pragma once
#include "Camera.h"
#include "Transform.h"
#include <vector>
#include "Components/Component.h"
#include "Components/MeshRenderer.h"
class Entity
{
public:

	Renderer* renderer;
	Transform* transform;
	

	Entity(Transform* transform, Camera* camera);
	~Entity();
	void AttachComponent(Component* c);
	void UpdateEntity(float dt);
	void Render();
	template<typename Component> Component* GetComponent();
private:
	std::vector<Component*> Components;
	Camera* m_mainCamera;
	GLuint m_depthTexture;
};

template<typename Component>
inline Component * Entity::GetComponent()
{
	for (unsigned int i = 0; i < Components.size(); i++) {
		if (Component* foundComponent = dynamic_cast<Component*>(Components[i])) {
			return foundComponent;
		}
	}
	return NULL;
	
}
