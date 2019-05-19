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
	if (dynamic_cast<Renderer*>(c)) {
		renderer = dynamic_cast<Renderer*>(c);
	}
	//c->InitializeComponent(this, m_mainCamera, transform, 0);
}

void Entity::UpdateEntity(float dt)
{
	for (auto const& c : Components) 
	{
		c->UpdateComponent(m_mainCamera,transform,dt);
	}
}

void Entity::Render()
{
	if (renderer != NULL) {
		renderer->DrawMesh();
	}
}