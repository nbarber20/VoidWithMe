#pragma once
#include<string>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
class Texture
{
public:
public:
	Texture();
	Texture(const std::string& fileName); 
	Texture(std::vector<std::string> filenames);
	void Use();
	virtual ~Texture();
	inline GLuint GetTexture() const {
		return  m_texture;
	}

protected:
private:
	GLuint m_texture;
};

