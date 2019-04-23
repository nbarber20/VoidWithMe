#pragma once
#include "Component.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../Model.h"
class MeshRenderer : public Component
{
public:
	MeshRenderer(Shader* shader, Texture* texture, Model* mesh);
	~MeshRenderer();
	void UpdateComponent(Camera* mainCamera, Transform transform) override;
	void DrawMesh();
private:
	Shader* m_shader;
	Texture* m_texture;
	Model* m_model;
};