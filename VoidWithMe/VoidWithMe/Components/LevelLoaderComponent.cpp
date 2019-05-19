#include "LevelLoaderComponent.h"


LevelLoaderComponent::LevelLoaderComponent(LevelLoader* lvlLoader,string levelToLoad, Entity* e)
{
	m_LevelLoader = lvlLoader;
	m_levelToLoad = levelToLoad;
	collider = e->GetComponent<BoxCollider>();
}

LevelLoaderComponent::~LevelLoaderComponent()
{

}

void LevelLoaderComponent::UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime)
{
	if (collider->isOverlapping) {
		m_LevelLoader->LoadLevel(m_levelToLoad);
	}
}

