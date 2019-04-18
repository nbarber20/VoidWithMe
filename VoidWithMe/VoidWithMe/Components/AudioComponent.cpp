#include "AudioComponent.h"


AudioComponent::AudioComponent(irrklang::ISoundEngine * engine, bool make3d, bool makeloop)
{
	SoundEngine = engine;
	is3d = make3d;
	doLoop = makeloop;
	Sound = SoundEngine->addSoundSourceFromFile("./resource/breakout.mp3");
	
}

AudioComponent::~AudioComponent()
{
}

void AudioComponent::UpdateComponent(Camera * mainCamera, Transform transform)
{

	if (!SoundEngine->isCurrentlyPlaying(Sound)) {

		if (is3d) {
			CurrentSound = SoundEngine->play3D(Sound, position, doLoop,false,true,false);
		}
		else {
			CurrentSound = SoundEngine->play2D(Sound, doLoop,false, true, false);
		}
	}
	position = irrklang::vec3df(transform.GetPos()->x, transform.GetPos()->y, transform.GetPos()->z);
	CurrentSound->setPosition(position);
}
