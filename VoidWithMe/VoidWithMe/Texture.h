#pragma once
#include<string>
#include <GL/glew.h>
#include "Shader.h"
#include <vector>
class Texture
{
public:
public:
	Texture();
	Texture(const std::string& fileName);
	void MakeCubeMap(std::vector<std::string> filenames);
	void Use(Shader* shader);
	virtual ~Texture();
	inline GLuint GetTexture() const {
		return  m_texture;
	}
protected:
private:

	GLuint m_texture;
};

