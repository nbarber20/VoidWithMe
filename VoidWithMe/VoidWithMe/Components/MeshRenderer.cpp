#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Shader* shader, Texture* texture, Mesh* mesh)
{
	m_shader = shader;
	m_texture = texture;
	m_mesh = mesh;
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::UpdateComponent(Camera* mainCamera, Transform transform, GLuint depthTexture)
{
	m_shader->Bind();
	m_texture->Bind();
	m_mesh->Draw();
}

