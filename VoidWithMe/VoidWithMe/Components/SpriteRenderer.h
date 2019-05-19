#pragma once
#include "Renderer.h"
class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer(Shader* shader, Texture* texture, Model* mesh, float speed,bool billboard,float XSlice,float XMax);
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
	void DrawMesh() override;
private:
	Shader* m_shader;
	Texture* m_texture;
	Model* m_model;
	glm::vec2 textureOffset;
	float animationTime;
	float animationSpeed;
	float LastFrame;
	bool billboard;
	float m_xSlice;
	float m_xMax;
};