#include "Skybox.h"
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"

Skybox::Skybox(std::vector<std::string> CubeMap)
{
	







	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};








	glGenVertexArrays(1, &m_skyboxVOA);
	glGenBuffers(1, &m_skyboxVBO);
	glBindVertexArray(m_skyboxVOA);
	glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	m_skyboxCubemap = new Texture();
	m_skyboxCubemap->MakeCubeMap(CubeMap);

	m_skyboxShader = new Shader("./resource/Shaders/skybox.vs", "./resource/Shaders/skybox.fs");








	m_skyboxShader->use();

	glm::mat4 projection = glm::perspective(70.0f, (float)800 / (float)600, 0.1f, 100.0f);
	m_skyboxShader->setInt("skybox", 0);
	m_skyboxShader->setMat4("projection", projection);











}


Skybox::~Skybox()
{
}

void Skybox::Draw(Camera camera)
{
	//DrawSkybox
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	m_skyboxShader->use();
	//glm::mat4 projection = glm::mat4(glm::mat3(camera.GetViewMatrix()));
	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	m_skyboxShader->setMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));	
	
	// skybox cube
	glBindVertexArray(m_skyboxVOA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxCubemap->GetTexture());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default


}

