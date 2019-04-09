#include "BoxCollider.h"



BoxCollider::BoxCollider(glm::vec3 Offset, glm::vec3 Scale)
{
	
	boundingBox =  AABB(glm::vec3(-Scale.x, -Scale.y, -Scale.z), glm::vec3(Scale.x, Scale.y, Scale.z));
	this->Scale = Scale;
}


BoxCollider::~BoxCollider()
{

}

void BoxCollider::UpdateComponent(Camera * mainCamera, Transform transform)
{
	boundingBox = AABB(*transform.GetPos()-(Scale/2.0f), *transform.GetPos()+(Scale/2.0f));
}

bool BoxCollider::PointOverlap(glm::vec3 Origin)
{
	return (Origin.x >= boundingBox.GetMin()->x && Origin.x <= boundingBox.GetMax()->x) &&
		(Origin.y >= boundingBox.GetMin()->y && Origin.y <= boundingBox.GetMax()->y) &&
		(Origin.z >= boundingBox.GetMin()->z && Origin.z <= boundingBox.GetMax()->z);
}

void BoxCollider::Draw()
{
}
