#pragma once
#include "Component.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../Mesh.h"
class MeshRenderer : public Component
{
public:
	MeshRenderer(Shader* shader, Texture* texture, Mesh* mesh);
	~MeshRenderer();
	void UpdateComponent(Camera* mainCamera, Transform transform) override;
	void DrawMesh();
private:
	Shader* m_shader;
	Texture* m_texture;
	Mesh* m_mesh;
};