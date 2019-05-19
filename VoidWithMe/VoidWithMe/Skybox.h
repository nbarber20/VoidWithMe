#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Display.h"
class Skybox
{
public:
	Skybox(std::string Filename, Display* display);
	void Set(std::string Filename);
	void Draw(Camera camera);
	~Skybox();

private:
	Shader* m_skyboxShader;
	Texture* m_skyboxCubemap;
	GLuint m_skyboxVOA;
	GLuint m_skyboxVBO;
};

