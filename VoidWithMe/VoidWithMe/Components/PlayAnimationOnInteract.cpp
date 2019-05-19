#include "PlayAnimationOnInteract.h"

PlayAnimationOnInteract::PlayAnimationOnInteract(Entity* e, Input* i) {
	collider = e->GetComponent<BoxCollider>();
	animation = e->GetComponent<AnimationComponent>();
	input = i;
}
void PlayAnimationOnInteract::UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) {

	if (collider->isOverlapping) {
		input->ShowText();
		if (input->Interacting) {
			animation->Play();
		}
	}
}