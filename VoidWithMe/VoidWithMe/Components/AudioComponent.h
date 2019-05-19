#pragma once
#include "Component.h"
#include <string>
#include "Klang/irrKlang.h"
#include <vector>

class AudioComponent : public Component
{
public:
	AudioComponent(irrklang::ISoundEngine* engine, std::vector<std::string> Files,bool make3d, bool makeloop, bool paused,bool playAll,float Volume);
	AudioComponent(irrklang::ISoundEngine* engine, std::string Files, bool make3d, bool makeloop, bool paused, bool playAll, float Volume);
	~AudioComponent();
	void UpdateComponent(Camera* mainCamera, Transform* transform, float DeltaTime) override;
	void Play();
	void PlayAll();
	void SetSound(std::string File) {
		Sounds.clear();
		Sounds.push_back(SoundEngine->getSoundSource(File.c_str(), true));
	}
private:
	irrklang::ISoundEngine* SoundEngine;
	std::vector<irrklang::ISoundSource*> Sounds;
	irrklang::ISound* CurrentSound;
	bool doLoop;
	bool is3d;
	bool doplayAll;
	
	bool paused;
	irrklang::vec3df position;
};
