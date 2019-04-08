#include "Entity.h"
#include "GL/glew.h"


Entity::Entity(Transform transform, Camera* camera,GLuint depthTexture)
{
	m_transform = transform;
	m_mainCamera = camera;
}


Entity::~Entity()
{
}

void Entity::AttachComponent(Component* c)
{
	Components.push_back(c);
}

void Entity::UpdateEntity()
{
	for (auto const& c : Components) 
	{
		c->UpdateComponent(m_mainCamera,m_transform,m_depthTexture);
	}
}
