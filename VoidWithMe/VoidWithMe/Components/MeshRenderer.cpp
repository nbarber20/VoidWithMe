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

void MeshRenderer::UpdateComponent(Camera* mainCamera, Transform transform)
{
	m_texture->Use(m_shader);
	m_shader->Update(transform, *mainCamera);
	m_mesh->Draw();
}

void MeshRenderer::DrawMesh()
{
	m_mesh->Draw();
}

