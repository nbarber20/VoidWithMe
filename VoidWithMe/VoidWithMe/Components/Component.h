#pragma once
#include "../Camera.h"
#include "../Transform.h"
#include "GL/glew.h"
class Component
{
public:
	Component();
	~Component();
	virtual void UpdateComponent(Camera* mainCamera, Transform transform);
};

