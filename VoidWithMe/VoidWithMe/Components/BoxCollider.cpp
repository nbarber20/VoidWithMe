#include "BoxCollider.h"



BoxCollider::BoxCollider(Entity* e, glm::vec3 Offset, glm::vec3 Scale, bool Trigger)
{
	
	boundingBox = AABB(*e->transform->GetPos() - (Scale / 2.0f), *e->transform->GetPos() + (Scale / 2.0f));
	this->Scale = Scale;
	this->isTrigger = Trigger;
}


BoxCollider::~BoxCollider()
{

}

void BoxCollider::UpdateComponent(Camera * mainCamera, Transform* transform, float DeltaTime)
{
	boundingBox = AABB(*transform->GetPos()-(Scale/2.0f), *transform->GetPos()+(Scale/2.0f));
}

bool BoxCollider::PointOverlap(glm::vec3 Origin)
{
	if((Origin.x >= boundingBox.GetMin()->x && Origin.x <= boundingBox.GetMax()->x) &&
		(Origin.y >= boundingBox.GetMin()->y && Origin.y <= boundingBox.GetMax()->y) &&
		(Origin.z >= boundingBox.GetMin()->z && Origin.z <= boundingBox.GetMax()->z)) {
		isOverlapping = true;
		return true;
	}
	else{
		isOverlapping = false;
		return false;
	}
}

void BoxCollider::Draw()
{
}
