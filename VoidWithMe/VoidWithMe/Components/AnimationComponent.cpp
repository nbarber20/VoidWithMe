#include "AnimationComponent.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" 
#include "rapidjson/filereadstream.h"
#include "../Transform.h"

#include <iostream>
using namespace rapidjson;



AnimationComponent::AnimationComponent(std::string filename) {
	FILE* fp = fopen(filename.c_str(), "rb"); // non-Windows use "r"
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document LevelDocument;
	LevelDocument.ParseStream(is);
	fclose(fp);

	for (auto& m : LevelDocument.GetObject()) // For each keyframe
	{
		float Time = std::stof(m.name.GetString());
		glm::vec3 Pos;
		Pos.x = m.value.GetObject()["Position"].GetObject()["X"].GetFloat();
		Pos.y = m.value.GetObject()["Position"].GetObject()["Y"].GetFloat();
		Pos.z = m.value.GetObject()["Position"].GetObject()["Z"].GetFloat();

		glm::vec3 Rot;
		Rot.x = m.value.GetObject()["Rotation"].GetObject()["X"].GetFloat();
		Rot.y = m.value.GetObject()["Rotation"].GetObject()["Y"].GetFloat();
		Rot.z = m.value.GetObject()["Rotation"].GetObject()["Z"].GetFloat();

		glm::vec3 Scale;
		Scale.x = m.value.GetObject()["Scale"].GetObject()["X"].GetFloat();
		Scale.y = m.value.GetObject()["Scale"].GetObject()["Y"].GetFloat();
		Scale.z = m.value.GetObject()["Scale"].GetObject()["Z"].GetFloat();
		Transform transform(Pos, Rot, Scale);
		
		keyFrames.push_back(KeyFrame(Time, transform));
	}
	AnimationTime = 0;



}
void AnimationComponent::UpdateComponent(Camera * mainCamera, Transform* transform, float DeltaTime)
{
	AnimationTime += DeltaTime;
	//std::cout << AnimationTime << std::endl;
	if (AnimationTime >= keyFrames[currentKeyframe].Time) {
		if (keyFrames.size()-1 > currentKeyframe) {
			currentKeyframe++;
			LastPos = *transform;
		}
	}

	float time = (AnimationTime- keyFrames[currentKeyframe-1].Time) / keyFrames[currentKeyframe].Time;
	//std::cout << time << std::endl;
	if(time<1){
		glm::vec3 newPos = lerp(time, *LastPos.GetPos(), *keyFrames[currentKeyframe].transform.GetPos());
		transform->SetPos(newPos);

		glm::vec3 newRot = lerp(time, *LastPos.GetRot(), *keyFrames[currentKeyframe].transform.GetRot());
		transform->SetRot(newRot);

		glm::vec3 newScale = lerp(time, *LastPos.GetScale(), *keyFrames[currentKeyframe].transform.GetScale());
		transform->SetScale(newScale);

	}

} 

glm::vec3 AnimationComponent::lerp(float t, const glm::vec3 a, const glm::vec3 b) {
	return (1 - t)*a + t * b;
}