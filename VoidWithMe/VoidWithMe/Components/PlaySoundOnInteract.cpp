#include "PlaySoundOnInteract.h"

PlaySoundOnInteract::PlaySoundOnInteract(Entity* e,Input* i) {
	collider = e->GetComponent<BoxCollider>();
	audio = e->GetComponent<AudioComponent>();
	input = i;
}
void PlaySoundOnInteract::UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) {	
	if (collider->isOverlapping) {
		input->ShowText();
		if (input->Interacting) {
			audio->Play();
		}
	}
}