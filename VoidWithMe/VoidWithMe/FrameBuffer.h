#pragma once
#include "GL/glew.h"
class FrameBuffer
{
public:
	FrameBuffer(int Width, int Height);
	~FrameBuffer();

	GLuint Buffer;
	GLuint Texture;
	GLuint rbo;
};

