#include "Entity.h"
#include "GL/glew.h"

Entity::Entity(Transform* transform, Camera* camera)
{
	this->transform = transform;
	m_mainCamera = camera;
}


Entity::~Entity()
{
}

void Entity::AttachComponent(Component* c)
{
	Components.push_back(c);
	if ((MeshRenderer*)c) {
		renderer = (MeshRenderer*)c;
	}
}

void Entity::UpdateEntity()
{
	for (auto const& c : Components) 
	{
		c->UpdateComponent(m_mainCamera,*transform);
	}
}

void Entity::Render()
{
	renderer->UpdateComponent(m_mainCamera, *transform);
}
