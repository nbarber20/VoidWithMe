#include "FrameBuffer.h"



FrameBuffer::FrameBuffer()
{
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	glGenFramebuffers(1, &Buffer);
	// create depth cubemap texture
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthTexture);
	for (unsigned int i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, Buffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


FrameBuffer::~FrameBuffer()
{


	glDeleteFramebuffers(1, &Buffer);
	glDeleteTextures(1, &depthTexture);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, Buffer);
	glViewport(0, 0, 1024, 1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	// We don't use bias in the shader, but instead we draw back faces, 
	// which are already separated from the front faces by a small distance 
	// (if your geometry is made this way)
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 800, 600); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles
}

void FrameBuffer::BindTexture()
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
}
