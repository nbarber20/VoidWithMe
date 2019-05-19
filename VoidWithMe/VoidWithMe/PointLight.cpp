#include "PointLight.h"
#include <vector>



PointLight::PointLight(glm::vec3 Position, Shader* shader, bool doshadows)
{
	this->Position = Position;
	Shadows = doshadows;

		depthShader = shader;
		const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
		glGenFramebuffers(1, &FrameBufferFBO);
		// create depth cubemap texture
		glGenTextures(1, &FrameBufferTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, FrameBufferTexture);
		for (unsigned int i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, FrameBufferTexture, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
}


PointLight::~PointLight()
{

	depthShader->~Shader();
	glDeleteFramebuffers(1, &FrameBufferFBO);
	glDeleteTextures(1, &FrameBufferTexture);
}

void PointLight::LightPass(std::vector<Entity*> sceneEntities)
{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float near_plane = 1.0f;
		float far_plane = 1000.0f;
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


		//render light

		glViewport(0, 0, 1024, 1024);
		glDisable(GL_CULL_FACE);
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		depthShader->use();
		for (unsigned int i = 0; i < 6; ++i)
			depthShader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms2[i]);
		depthShader->setFloat("far_plane", far_plane);
		depthShader->setVec3("lightPos", Position);

		for (unsigned int i = 0; i < sceneEntities.size(); i++) {
			depthShader->setMat4("model", sceneEntities[i]->transform->GetModel());
			sceneEntities[i]->Render();

		}
		//renderScene(simpleDepthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	

		glEnable(GL_CULL_FACE);

}
