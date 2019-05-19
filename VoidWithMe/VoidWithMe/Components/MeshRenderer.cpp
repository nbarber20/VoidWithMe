#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Shader* shader, Texture* texture, Model* model)
{
	m_shader = shader;
	m_texture = texture;
	m_model = model;
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime)
{
	m_shader->use();
	m_texture->Use();
	m_shader->Update(*transform, *mainCamera);
	m_model->Draw();
}

void MeshRenderer::DrawMesh()
{
	m_model->Draw();
}

