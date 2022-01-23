#include "Editor.h"
#include "SceneIntro.h"
#include "Log.h"
#include "Engine.h"
#include "Camera3D.h"
#include "Renderer3D.h"
#include "Window.h"
#include "Primitive.h"
#include <iostream>
#include <fstream>
#include "SDL_assert.h"
#include "RNG.h"
#include "ImGuiAppLog.h"
#include "FileSystem.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"
#include "GameObject.h"
#include "Lua.h"
#include "Input.h"
#include "SceneManager.h"

#include "ComponentMaterial.h" // Temporal for the assignment, just to display the texture on the model when the program begins...

SceneIntro::SceneIntro(HoneyEngine* engine) : Scene()
{
	name = "SceneIntro";
	// Needed modules
	this->engine = engine;

	jsonHandler.LoadJson(j,"EngineConfig/window_test.json");
	rootGo = new GameObject(-1, engine, "Root");
	gameObjectList.push_back(rootGo);
	
}

SceneIntro::~SceneIntro()
{
	CleanUp();
}

// Load assets
bool SceneIntro::Start()
{
	CONSOLE_LOG("Loading Intro assets");
	appLog->AddLog("Loading Intro assets\n");
	bool ret = true;

	// Load scene with a camera and several houses.
	engine->GetSceneManager()->LoadScene(this, "SceneIntro");

	return ret;
}

bool SceneIntro::PreUpdate(float dt)
{
	for (GameObject* go : this->gameObjectList)
	{
		go->PreUpdate();
	}

	return true;
}

// Update
bool SceneIntro::Update(float dt)
{
	if (engine->GetSceneManager()->runtimeState == RuntimeState::PLAYING)
	{
		lua = new Lua(engine);
		
		lua->luaWork->GetPosCScript();

		if (engine->GetInput()->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			//bulletRot = true;
			lua->luaWork->CreateBullet();
			
		}

		std::vector<GameObject*>::iterator item = gameObjectList.begin();
		while (item != gameObjectList.end())
		{
			if ((*item)->name.compare("Bullet") == 0 && (*item) != nullptr)
			{
				if ((*item)->GetTransform() != nullptr)
				{
					if ((*item)->GetTransform()->GetPosition().y < -100)
					{
						DeleteGameObject(*item);
						lua->luaWork->bulletExists = false;
					}
				}
				break;
			}
			item++;
		}
	}

	for (GameObject* go : this->gameObjectList)
	{
		go->Update();
	}

	return true;
}

bool SceneIntro::PostUpdate(float dt)
{
	// Draw meshes
	for (GameObject* go : this->gameObjectList)
	{
		go->PostUpdate();
	}

	engine->GetRenderer()->DrawRay();
	return true;
}

// Load assets
bool SceneIntro::CleanUp()
{
	CONSOLE_LOG("Unloading Intro scene");
	appLog->AddLog("Unloading Intro scene\n");

	for (GameObject* gameObject : gameObjectList)
	{
		RELEASE(gameObject);
	}

	RELEASE(lua);

	return true;
}
