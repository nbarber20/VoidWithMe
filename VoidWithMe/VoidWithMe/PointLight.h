#pragma once
#include "glm/gtx/transform.hpp"
#include "Entity.h"
class PointLight
{
public:
	PointLight(glm::vec3 Position, Shader* shader, bool doshadows);
	~PointLight();
	void LightPass(std::vector<Entity*> sceneEntities);
	glm::vec3 Position;
	GLuint FrameBufferFBO;
	GLuint FrameBufferTexture;
	Shader* depthShader;
	bool Shadows;
};

