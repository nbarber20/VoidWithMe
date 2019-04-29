#include "AudioComponent.h"


AudioComponent::AudioComponent(irrklang::ISoundEngine * engine, std::string File, bool make3d, bool makeloop, bool paused)
{
	SoundEngine = engine;
	is3d = make3d;
	doLoop = makeloop;
	Sound = SoundEngine->addSoundSourceFromFile(File.c_str());
	if (is3d) {
		CurrentSound = SoundEngine->play3D(Sound, position, doLoop, paused, true, false);
	}
	else {
		CurrentSound = SoundEngine->play2D(Sound, doLoop, paused, true, false);
	}
	this->paused = paused;
}

AudioComponent::~AudioComponent()
{
}

void AudioComponent::UpdateComponent(Camera * mainCamera, Transform* transform, float DeltaTime)
{
	if (CurrentSound != NULL) {
		position = irrklang::vec3df(transform->GetPos()->x, transform->GetPos()->y, transform->GetPos()->z);
		CurrentSound->setPosition(position);
	}
}

void AudioComponent::Play()
{
	CurrentSound->setIsPaused(false);
}
