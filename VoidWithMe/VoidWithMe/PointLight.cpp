#include "PointLight.h"
#include <vector>



PointLight::PointLight(glm::vec3 Position)
{
	this->Position = Position;
	depthShader = new Shader("./resource/Shaders/point_shadows_depth.vs", "./resource/Shaders/point_shadows_depth.fs", "./resource/Shaders/point_shadows_depth.gs");
	ShadowMapBuffer = new FrameBuffer();
}


PointLight::~PointLight()
{
}

void PointLight::LightPass(std::vector<Entity> sceneEntities)
{

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float near_plane = 1.0f;
	float far_plane = 100.0f;
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)1024 / (float)1024, near_plane, far_plane);

	// 0. create depth cubemap transformation matrices
		// -----------------------------------------------
	std::vector<glm::mat4> shadowTransforms2;
	shadowTransforms2.push_back(shadowProj * glm::lookAt(Position, Position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms2.push_back(shadowProj * glm::lookAt(Position, Position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms2.push_back(shadowProj * glm::lookAt(Position, Position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms2.push_back(shadowProj * glm::lookAt(Position, Position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms2.push_back(shadowProj * glm::lookAt(Position, Position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms2.push_back(shadowProj * glm::lookAt(Position, Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));


	//render light 2

	glViewport(0, 0, 1024, 1024);
	glBindFramebuffer(GL_FRAMEBUFFER, ShadowMapBuffer->Buffer);
	glClear(GL_DEPTH_BUFFER_BIT);
	depthShader->use();
	for (unsigned int i = 0; i < 6; ++i)
		depthShader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms2[i]);
	depthShader->setFloat("far_plane", far_plane);
	depthShader->setVec3("lightPos", Position);

	for (unsigned int i = 0; i < sceneEntities.size(); i++) {
		depthShader->setMat4("model", sceneEntities[i].transform->GetModel());
		sceneEntities[i].renderer->DrawMesh();

	}
	//renderScene(simpleDepthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	

}
