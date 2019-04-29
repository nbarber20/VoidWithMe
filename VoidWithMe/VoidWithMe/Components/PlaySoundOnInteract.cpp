#include "PlaySoundOnInteract.h"

PlaySoundOnInteract::PlaySoundOnInteract(Entity* e ) {
	collider = e->GetComponent<BoxCollider>();
	audio = e->GetComponent<AudioComponent>();
}
void PlaySoundOnInteract::UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) {
	
	if (collider->isOverlapping) {
		audio->Play();
	}
}