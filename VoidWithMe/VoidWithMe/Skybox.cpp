#include "Skybox.h"
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"

Skybox::Skybox(std::string Filename, Display* display)
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

	std::vector<std::string> CubeMap
	{
		Filename + "right.jpg",
		Filename + "left.jpg",
		Filename + "top.jpg",
		Filename + "bottom.jpg",
		Filename + "front.jpg",
		Filename + "back.jpg"
	};
	m_skyboxCubemap = new Texture(CubeMap);






	glGenVertexArrays(1, &m_skyboxVOA);
	glGenBuffers(1, &m_skyboxVBO);
	glBindVertexArray(m_skyboxVOA);
	glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	

	m_skyboxShader = new Shader("./resource/Shaders/skybox.vs", "./resource/Shaders/skybox.fs");








	m_skyboxShader->use();

	glm::mat4 projection = glm::perspective(70.0f, (float)display->Width / (float)display->Height, 0.1f, 100.0f);
	m_skyboxShader->setInt("skybox", 0);
	m_skyboxShader->setMat4("projection", projection);











}


Skybox::~Skybox()
{

}
void Skybox::Set(std::string Filename) {
	std::vector<std::string> CubeMap
	{
		Filename + "right.jpg",
		Filename + "left.jpg",
		Filename + "top.jpg",
		Filename + "bottom.jpg",
		Filename + "front.jpg",
		Filename + "back.jpg"
	};
	m_skyboxCubemap = new Texture(CubeMap);
}

void Skybox::Draw(Camera camera)
{
	//DrawSkybox
	glDepthFunc(GL_LEQUAL); 
	m_skyboxShader->use();
	m_skyboxCubemap->Use();
	m_skyboxShader->setMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxCubemap->GetTexture());

	glBindVertexArray(m_skyboxVOA);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default


}

