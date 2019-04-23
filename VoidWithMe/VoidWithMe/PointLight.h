#pragma once
#include "FrameBuffer.h"
#include "glm/gtx/transform.hpp"
#include "Entity.h"
class PointLight
{
public:
	PointLight(glm::vec3 Position);
	~PointLight();
	void LightPass(std::vector<Entity> sceneEntities);
	glm::vec3 Position;
	FrameBuffer* ShadowMapBuffer;
	Shader* depthShader;
};

