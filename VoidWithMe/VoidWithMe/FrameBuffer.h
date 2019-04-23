#pragma once
#include "GL/glew.h"
#include "Shader.h"
class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();
	void Bind();
	void Render();
	void BindTexture();

	GLuint Buffer;

	GLuint depthTexture;
};

