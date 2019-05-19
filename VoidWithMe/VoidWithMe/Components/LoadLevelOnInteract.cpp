#include "LoadLevelOnInteract.h"

LoadLevelOnInteract::LoadLevelOnInteract(LevelLoader * lvlLoader, string levelToLoad, string tooltip, Entity * e, Input * i)
{
	collider = e->GetComponent<BoxCollider>();
	input = i;
	lvl = levelToLoad;
	this->lvlLoader = lvlLoader;
	this->tooltip = tooltip;
}

void LoadLevelOnInteract::UpdateComponent(Camera * mainCamera, Transform * transform, float DeltaTime)
{
	if (collider->isOverlapping) {
		input->ShowText(tooltip);
		if (input->Interacting) {
			lvlLoader->LoadLevel(lvl);
		}
	}
}
