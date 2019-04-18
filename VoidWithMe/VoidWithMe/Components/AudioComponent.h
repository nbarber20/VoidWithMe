#pragma once
#include "Component.h"
#include "Klang/irrKlang.h"

class AudioComponent : public Component
{
public:
	AudioComponent(irrklang::ISoundEngine* engine, bool make3d, bool makeloop);
	~AudioComponent();
	void UpdateComponent(Camera* mainCamera, Transform transform) override;
private:
	irrklang::ISoundEngine* SoundEngine;
	irrklang::ISoundSource* Sound;
	irrklang::ISound* CurrentSound;
	bool doLoop;
	bool is3d;
	irrklang::vec3df position;
};
