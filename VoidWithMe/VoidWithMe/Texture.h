#pragma once
#include<string>
#include <GL/glew.h>
class Texture
{
public:
public:
	Texture(const std::string& fileName);
	void Bind();
	virtual ~Texture();
	inline GLuint GetTexture() const {
		return  m_texture;
	}
protected:
private:

	GLuint m_texture;
};

