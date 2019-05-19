#pragma once
#include "Renderer.h"
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(Shader* shader, Texture* texture, Model* mesh);
	~MeshRenderer();
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
	void DrawMesh() override;
private:
	Shader* m_shader;
	Texture* m_texture;
	Model* m_model;
};