#include "AudioComponent.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>

AudioComponent::AudioComponent(irrklang::ISoundEngine * engine, std::vector<std::string> Files, bool make3d, bool makeloop, bool paused, bool playAll, float Volume)
{
	SoundEngine = engine;
	is3d = make3d;
	doLoop = makeloop;
	for (int i = 0; i < Files.size(); i++) {
		Sounds.push_back(SoundEngine->getSoundSource(Files[i].c_str(), true));
		Sounds[i]->setDefaultVolume(Volume);
	}
	this->doplayAll = playAll;
	if (!paused) {
		Play();
	}
}
AudioComponent::AudioComponent(irrklang::ISoundEngine * engine, std::string Files, bool make3d, bool makeloop, bool paused, bool playAll, float Volume)
{
	SoundEngine = engine;
	is3d = make3d;
	doLoop = makeloop;

	Sounds.push_back(SoundEngine->getSoundSource(Files.c_str(), true));
	Sounds[0]->setDefaultVolume(Volume);
	this->doplayAll = playAll;
	if (!paused) {
		Play();
	}
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
	if (doplayAll) {
		PlayAll();
	}
	else {
		int i = 0;
		if (Sounds.size() > 1) {
			srand(time(NULL));
			i = rand() % Sounds.size();
		}

		bool isplaying = false;
		for (int j = 0; j < Sounds.size(); j++) {
			if (SoundEngine->isCurrentlyPlaying(Sounds[j])) {
				isplaying = true;
			}
		}

		if (!isplaying) {
			if (is3d) {
				CurrentSound = SoundEngine->play3D(Sounds[i], position, doLoop, false, true, false);
			}
			else {
				CurrentSound = SoundEngine->play2D(Sounds[i], doLoop, false, true, false);
			}
		}
	}
}

void AudioComponent::PlayAll() {
	for (int j = 0; j < Sounds.size(); j++) {
		if (!SoundEngine->isCurrentlyPlaying(Sounds[j])) {
			if (is3d) {
				CurrentSound = SoundEngine->play3D(Sounds[j], position, doLoop, false, true, false);
			}
			else {
				CurrentSound = SoundEngine->play2D(Sounds[j], doLoop, false, true, false);
			}
		}
	}
}