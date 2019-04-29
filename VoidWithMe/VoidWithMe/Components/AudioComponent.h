#pragma once
#include "Component.h"
#include <string>
#include "Klang/irrKlang.h"

class AudioComponent : public Component
{
public:
	AudioComponent(irrklang::ISoundEngine* engine, std::string File,bool make3d, bool makeloop, bool paused);
	~AudioComponent();
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
	void Play();
private:
	irrklang::ISoundEngine* SoundEngine;
	irrklang::ISoundSource* Sound;
	irrklang::ISound* CurrentSound;
	bool doLoop;
	bool is3d;
	bool paused;
	irrklang::vec3df position;
};
