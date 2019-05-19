#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader* shader, Texture* texture, Model* model,float speed, bool billboard, float XSlice,float XMax)
{
	m_shader = shader;
	m_texture = texture;
	m_model = model;
	animationSpeed = speed;
	this->billboard = billboard;
	m_xSlice = XSlice;
	m_xMax = XMax;
}

void SpriteRenderer::UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime)
{
	animationTime += DeltaTime;
	m_texture->Use();
	m_shader->use();

	if (billboard) {
		glm::mat4 newtransform = glm::lookAt(*transform->GetPos(), mainCamera->position, glm::vec3(0, 1, 0));
		transform->SetModel(glm::inverse(newtransform));
	}

	m_shader->setMat4("projection", mainCamera->perspective);
	m_shader->setMat4("view", mainCamera->GetViewMatrix());
	m_shader->setVec3("viewPos", mainCamera->position);


	if (animationTime - LastFrame > animationSpeed) {

		LastFrame = animationTime;
		float index = textureOffset.x + (m_xSlice / m_xMax);
		if (index > m_xMax) {
			index = 0;
		}

		textureOffset = glm::vec2(index, 0);
	}
	m_shader->setVec2("Offset", textureOffset);
	m_shader->setVec2("Size", glm::vec2(m_xSlice / m_xMax, 1));
	m_shader->setMat4("model", transform->GetModel());
	m_model->Draw();
}

void SpriteRenderer::DrawMesh()
{
	//m_model->Draw();
}


