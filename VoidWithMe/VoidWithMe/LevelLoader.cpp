#include "LevelLoader.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filereadstream.h"
#include "Components/AudioComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/PlaySoundOnInteract.h"
#include "Entity.h"
using namespace rapidjson;
LevelLoader::LevelLoader()
{
}


LevelLoader::~LevelLoader()
{
}

void LevelLoader::LoadLevel(std::string FileName, std::vector<Entity*>* SceneArray, std::vector<PointLight*>* LightArray, std::vector<BoxCollider*>* colliderArray, Camera* camera, Shader* modelShader, Shader* lightShader, irrklang::ISoundEngine* AudioEngine)
{
	LightArray->clear();
	SceneArray->clear();
	colliderArray->clear();

	FILE* fp = fopen(FileName.c_str(), "rb"); // non-Windows use "r"
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document LevelDocument;
	LevelDocument.ParseStream(is);
	fclose(fp);
	for (auto& m : LevelDocument.GetObject()["Objects"].GetObject()) // For each gameobject
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

		if (m.value["Components"].GetObject().HasMember("MeshRenderer")) { //Add MeshRender
			string ModelFile = m.value["Components"].GetObject()["MeshRenderer"].GetObject()["Model"].GetString();
		    string TextureFile = m.value["Components"].GetObject()["MeshRenderer"].GetObject()["Texture"].GetString();
			newEntity->AttachComponent(new MeshRenderer(modelShader, new Texture(TextureFile), new Model(ModelFile)));
		}
		if (m.value["Components"].GetObject().HasMember("BoxCollider")) { //Add BoxCollider
			glm::vec3 Size;
			Size.x = m.value["Components"].GetObject()["BoxCollider"].GetObject()["Size"].GetObject()["X"].GetFloat();
			Size.y = m.value["Components"].GetObject()["BoxCollider"].GetObject()["Size"].GetObject()["Y"].GetFloat();
			Size.z = m.value["Components"].GetObject()["BoxCollider"].GetObject()["Size"].GetObject()["Z"].GetFloat();
			glm::vec3 Offset;
			Offset.x = m.value["Components"].GetObject()["BoxCollider"].GetObject()["Offset"].GetObject()["X"].GetFloat();
			Offset.y = m.value["Components"].GetObject()["BoxCollider"].GetObject()["Offset"].GetObject()["Y"].GetFloat();
			Offset.z = m.value["Components"].GetObject()["BoxCollider"].GetObject()["Offset"].GetObject()["Z"].GetFloat();
			bool Trigger = m.value["Components"].GetObject()["BoxCollider"].GetObject()["Trigger"].GetBool();
			BoxCollider* newBoxCollider = new BoxCollider(newEntity,Offset,Size,Trigger);
			colliderArray->push_back(newBoxCollider);
			newEntity->AttachComponent(newBoxCollider);
		}
		if (m.value["Components"].GetObject().HasMember("Audio")) { //Add Sound
			string AudioFile = m.value["Components"].GetObject()["Audio"].GetObject()["File"].GetString();
			bool Make3d = m.value["Components"].GetObject()["Audio"].GetObject()["3D"].GetBool();
			bool Loop = m.value["Components"].GetObject()["Audio"].GetObject()["Loop"].GetBool();
			bool Paused = m.value["Components"].GetObject()["Audio"].GetObject()["Paused"].GetBool();
			newEntity->AttachComponent(new AudioComponent(AudioEngine, AudioFile,Make3d,Loop, Paused));
		}
		if (m.value["Components"].GetObject().HasMember("Animation")) { //Add Sound
			string AnimationFile = m.value["Components"].GetObject()["Animation"].GetObject()["File"].GetString();
			newEntity->AttachComponent(new AnimationComponent(AnimationFile));
		}
		if (m.value["Components"].GetObject().HasMember("PlaySoundOnInteract")) { //Add InteractOnPlaySound
			//BoxCollider* bc = newEntity->GetComponent<BoxCollider>();
			//AudioComponent* ac = newEntity->GetComponent<AudioComponent>();
			newEntity->AttachComponent(new PlaySoundOnInteract(newEntity));
		}
		SceneArray->push_back(newEntity);

	}
	for (auto& m : LevelDocument.GetObject()["Lights"].GetObject()) // For each light
	{

		glm::vec3 Position;
		bool CastShadows;
		Position.x = m.value["Position"].GetObject()["X"].GetFloat();
		Position.y = m.value["Position"].GetObject()["Y"].GetFloat();
		Position.z = m.value["Position"].GetObject()["Z"].GetFloat();
		CastShadows = m.value["Shadow"].GetBool();
		LightArray->push_back(new PointLight(Position, lightShader, CastShadows));

	}

	
	//Placeholder
	/*
	Entity FloorEntity(new Transform(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)), camera);
	FloorEntity.AttachComponent(new MeshRenderer(modelShader, new Texture("./resource/Materials/GroundTex.jpg"), new Model("./resource/Models/Ground.obj")));

	Entity ModelEntity(new Transform(glm::vec3(0.0f, -5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)), camera);
	ModelEntity.AttachComponent(new MeshRenderer(modelShader, new Texture("./resource/Materials/TreeTex.jpg"), new Model("./resource/Models/Tree.obj")));
	BoxCollider* ModelCollider = new BoxCollider(glm::vec3(0, 0, 0), glm::vec3(10, 100, 10));
	colliderArray->push_back(ModelCollider);
	ModelEntity.AttachComponent(ModelCollider);
	*/
	//SceneArray->push_back(ModelEntity);
	//SceneArray->push_back(FloorEntity);

	//LightArray->push_back(new PointLight(glm::vec3(-10,  5, 0), lightShader,true));
	//LightArray->push_back(new PointLight(glm::vec3(10, 5, 0), lightShader,false));

}
