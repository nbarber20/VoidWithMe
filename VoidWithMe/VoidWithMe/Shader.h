#pragma once

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Camera.h"

//remove
#include <string>
class Shader
{
public:
	Shader();
	Shader(const std::string& VertexFilename, const std::string& FragmentFilename);
	void operator=(const Shader& shader) {}
	Shader(const Shader& shader) {}

	void Bind();
	void Update(const Transform& transform, const Camera& camera);
	inline GLuint GetProgram() const {
		return m_program;
	}
	virtual ~Shader();
protected:
private:


	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;


	
	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];



	std::string DebugName;
};
