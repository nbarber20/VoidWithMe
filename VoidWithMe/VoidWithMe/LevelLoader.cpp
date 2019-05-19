#include "LevelLoader.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filereadstream.h"
#include "Components/AudioComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/PlaySoundOnInteract.h"
#include "Components/PlayAnimationOnInteract.h"
#include "Components/LevelLoaderComponent.h"
#include "Components/LoadLevelOnInteract.h"
#include "Components/SpriteRenderer.h"
#include "Entity.h"
using namespace rapidjson;
LevelLoader::LevelLoader(std::vector<Entity*>* SceneArray, std::vector<PointLight*>* LightArray, std::vector<BoxCollider*>* colliderArray, Camera* camera, Shader* modelShader, Shader* spriteShader, Shader* lightShader, Input* input, irrklang::ISoundEngine* AudioEngine, AudioComponent* FootstepSFX, Skybox* sky)
{
	this->SceneArray = SceneArray;
	this->LightArray = LightArray;
	this->colliderArray = colliderArray;
	this->camera =camera;
	this->modelShader=modelShader;
	this->spriteShader = spriteShader;
	this->lightShader=lightShader;
	this->input=input;
	this->AudioEngine=AudioEngine;
	this->FootStepSFX = FootstepSFX;
	this->sky = sky;
}



LevelLoader::~LevelLoader()
{
}

void LevelLoader::LoadLevel(std::string FileName)
{

	LightArray->clear();
	SceneArray->clear();
	colliderArray->clear();
	camera->position = glm::vec3(0.0f, 5.0f, 0.0f);
	AudioEngine->stopAllSounds();
	FILE* fp = fopen(FileName.c_str(), "rb"); 
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document LevelDocument;
	LevelDocument.ParseStream(is);
	fclose(fp);

	//For Each Gameobject
	for (auto& m : LevelDocument.GetObject()["Objects"].GetObject()) 
	{
		
		glm::vec3 Position;		
		Position.x = m.value["Position"].GetObject()["X"].GetFloat();
		Position.y = m.value["Position"].GetObject()["Y"].GetFloat();
		Position.z = m.value["Position"].GetObject()["Z"].GetFloat();
		glm::vec3 Rotation;
		Rotation.x = m.value["Rotation"].GetObject()["X"].GetFloat();
		Rotation.y = m.value["Rotation"].GetObject()["Y"].GetFloat();
		Rotation.z = m.value["Rotation"].GetObject()["Z"].GetFloat();
		glm::vec3 Scale;
		Scale.x = m.value["Scale"].GetObject()["X"].GetFloat();
		Scale.y = m.value["Scale"].GetObject()["Y"].GetFloat();
		Scale.z = m.value["Scale"].GetObject()["Z"].GetFloat();



		Entity* newEntity = new Entity(new Transform(Position, Rotation, Scale), camera);
		for (auto& Comp: m.value["Components"].GetObject()) {
			if (Comp.name.GetString() == (string)"BoxCollider") {
				glm::vec3 Size;
				Size.x = Comp.value["Size"].GetObject()["X"].GetFloat();
				Size.y = Comp.value["Size"].GetObject()["Y"].GetFloat();
				Size.z = Comp.value["Size"].GetObject()["Z"].GetFloat();
				glm::vec3 Offset;
				Offset.x = Comp.value["Offset"].GetObject()["X"].GetFloat();
				Offset.y = Comp.value["Offset"].GetObject()["Y"].GetFloat();
				Offset.z = Comp.value["Offset"].GetObject()["Z"].GetFloat();
				bool Trigger = Comp.value["Trigger"].GetBool();
				BoxCollider* newBoxCollider = new BoxCollider(newEntity, Offset, Size, Trigger);
				colliderArray->push_back(newBoxCollider);
				newEntity->AttachComponent(newBoxCollider);
			}
		}
		if (m.value["Components"].GetObject().HasMember("MeshRenderer")) { //Add MeshRender
			string ModelFile = m.value["Components"].GetObject()["MeshRenderer"].GetObject()["Model"].GetString();
			string TextureFile = m.value["Components"].GetObject()["MeshRenderer"].GetObject()["Texture"].GetString();
			newEntity->AttachComponent(new MeshRenderer(modelShader, new Texture(TextureFile), new Model(ModelFile)));
			
		}
		if (m.value["Components"].GetObject().HasMember("SpriteRenderer")) { //Add MeshRender
			string ModelFile = m.value["Components"].GetObject()["SpriteRenderer"].GetObject()["Model"].GetString();
			string TextureFile = m.value["Components"].GetObject()["SpriteRenderer"].GetObject()["Texture"].GetString();
		    float animationSpeed = m.value["Components"].GetObject()["SpriteRenderer"].GetObject()["Speed"].GetFloat();
			bool doBillboard = m.value["Components"].GetObject()["SpriteRenderer"].GetObject()["Billboard"].GetBool();
			float xSlice = m.value["Components"].GetObject()["SpriteRenderer"].GetObject()["XSlice"].GetFloat();
			float XMax = m.value["Components"].GetObject()["SpriteRenderer"].GetObject()["XMax"].GetFloat();
			newEntity->AttachComponent(new SpriteRenderer(spriteShader, new Texture(TextureFile), new Model(ModelFile), animationSpeed, doBillboard,xSlice,XMax));

		}
		if (m.value["Components"].GetObject().HasMember("Audio")) { //Add Sound
			vector<string> AudioFile;			

			if (m.value["Components"].GetObject()["Audio"].GetObject()["File"].IsArray()) {
				for (int i = 0; i < m.value["Components"].GetObject()["Audio"].GetObject()["File"].GetArray().Size(); i++) {

					AudioFile.push_back(m.value["Components"].GetObject()["Audio"].GetObject()["File"].GetArray()[i].GetString());
				}
			}
			else {
				AudioFile.push_back(m.value["Components"].GetObject()["Audio"].GetObject()["File"].GetString());
			}
			bool Make3d =  m.value["Components"].GetObject()["Audio"].GetObject()["3D"].GetBool();
			bool Loop =    m.value["Components"].GetObject()["Audio"].GetObject()["Loop"].GetBool();
			bool Paused =  m.value["Components"].GetObject()["Audio"].GetObject()["Paused"].GetBool();
			bool PlayAll = m.value["Components"].GetObject()["Audio"].GetObject()["PlayAll"].GetBool();
			float Volume = m.value["Components"].GetObject()["Audio"].GetObject()["Volume"].GetFloat();
			newEntity->AttachComponent(new AudioComponent(AudioEngine, AudioFile,Make3d,Loop, Paused, PlayAll, Volume));
		}
		if (m.value["Components"].GetObject().HasMember("Animation")) { //Add Sound
			string AnimationFile = m.value["Components"].GetObject()["Animation"].GetObject()["File"].GetString();
			bool Paused = m.value["Components"].GetObject()["Animation"].GetObject()["Paused"].GetBool();
			newEntity->AttachComponent(new AnimationComponent(AnimationFile, Paused));
		}
		if (m.value["Components"].GetObject().HasMember("PlaySoundOnInteract")) { //Add Play Sound On Interact
			newEntity->AttachComponent(new PlaySoundOnInteract(newEntity,input));
		}
		if (m.value["Components"].GetObject().HasMember("PlayAnimationOnInteract")) { //Add Play Anim On Interact
			newEntity->AttachComponent(new PlayAnimationOnInteract(newEntity, input));
		}
		if (m.value["Components"].GetObject().HasMember("LoadLevel")) { //Add LevelLoaderComponent
			string LevelFile = m.value["Components"].GetObject()["LoadLevel"].GetObject()["File"].GetString();
			newEntity->AttachComponent(new LevelLoaderComponent(this,LevelFile,newEntity));
		}
		if (m.value["Components"].GetObject().HasMember("LoadLevelOnInteract")) { //Add LevelLoaderComponent
			string LevelFile = m.value["Components"].GetObject()["LoadLevelOnInteract"].GetObject()["File"].GetString();
			string ToolTip = m.value["Components"].GetObject()["LoadLevelOnInteract"].GetObject()["ToolTip"].GetString();
			newEntity->AttachComponent(new LoadLevelOnInteract(this, LevelFile,ToolTip, newEntity,input));
		}
		SceneArray->push_back(newEntity);

	}

	//For each light
	for (auto& m : LevelDocument.GetObject()["Lights"].GetObject())
	{

		glm::vec3 Position;
		bool CastShadows;
		Position.x = m.value["Position"].GetObject()["X"].GetFloat();
		Position.y = m.value["Position"].GetObject()["Y"].GetFloat();
		Position.z = m.value["Position"].GetObject()["Z"].GetFloat();
		CastShadows = m.value["Shadow"].GetBool();
		LightArray->push_back(new PointLight(Position, lightShader, CastShadows));

	}
	FootStepSFX->SetSound(LevelDocument.GetObject()["FootStepSFX"].GetString());
	sky->Set(LevelDocument.GetObject()["Skybox"].GetString());
	
	
	//Ready the shader (this changes based on num of lights)
	modelShader->use();
	modelShader->setInt("Num_Lights", LightArray->size());
	modelShader->setInt("diffuseTexture", 0);
	for (unsigned int i = 0; i < LightArray->size(); i++) {

		modelShader->setInt("depthMap[" + std::to_string(i) + "]", i + 1);
	}
}
