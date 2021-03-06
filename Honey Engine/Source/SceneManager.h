#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "Module.h"
#include "Scene.h"

#include "Timer.h"
#include <string>
#include <list>

class HoneyEngine;
class SceneIntro;
class GameObject;
class JasonHandler;
class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;
class ComponentInfo;
class ComponentCamera;
class ComponentScript;

enum class RuntimeState
{
	PLAYING,
	PAUSED,
	STOPPED,
	TICK
};

class SceneManager : public Module
{
	//friend class Lua;
	//friend class LuaWorks;
public:
	SceneManager(HoneyEngine* engine);
	~SceneManager();

	// Called before render is available
	virtual bool Awake();

	// Called before the first frame
	virtual bool Start();

	// Called each loop iteration
	virtual bool PreUpdate(float dt);

	// Called each loop iteration
	virtual bool Update(float dt);

	// Called each loop iteration
	virtual bool PostUpdate(float dt);

	// Called before quitting
	virtual bool CleanUp();

	bool PrepareUpdate();
	bool FinishUpdate();

	void AddScene(Scene* scene);
	Scene* GetCurrentScene();
	RuntimeState GetState();

	void OnPlay();
	void OnStop();
	void OnPause();
	void OnResume();
	void OnTick();

	// Serialization functions
	bool SaveScene(Scene* scene);
	Json SaveComponentTransform(ComponentTransform* componentTransform);
	Json SaveComponentMesh(ComponentMesh* componentMesh);
	Json SaveComponentMaterial(ComponentMaterial* componentMaterial);
	Json SaveComponentInfo(ComponentInfo* componentInfo);
	Json SaveComponentScript(ComponentScript* componentScript);
	Json SaveComponentCamera(ComponentCamera* componentCamera);
	bool LoadScene(Scene* scene, const char* sceneName);
	void LoadComponentTransform(ComponentTransform* componentTransform, Json jsonComponentTransform);
	void LoadComponentMesh(ComponentMesh* componentMesh, Json jsonComponentMesh);
	void LoadComponentInfo(ComponentInfo* componentInfo, Json jsonComponentInfo);
	void LoadComponentScript(ComponentScript* componentScript, Json jsonComponentScript);
	void LoadComponentCamera(ComponentCamera* componentCamera, Json jsonComponentCamera);

public:
	bool active;
	Scene* currentScene = nullptr;
	RuntimeState runtimeState = RuntimeState::STOPPED;
	float gameDt = 0.0f;

private:
	// Modules
	HoneyEngine* engine = nullptr;

	// Scenes
	std::vector<Scene*> scenes;
	SceneIntro* sceneIntro = nullptr;

	// TIME MANAGEMENT
	// --------------------------------------------------
	// Frame Count: app graphics frames since game start
	uint frameCount = 0;
	// Time: second since game start (Game Clock)
	float time = 0.0f; // To keep the seconds when we pause the simulation
	// Time Scale: scale at which time is passing (Game Clock)
	// Modify this variable to change the speed of our game in runtime.
	float timeScale = 1.0f; // 1 --> Real Time / < 1 --> Slower / > 1 Faster, 0 Pause or Stop
	// Delta Time: last frame time expressed in seconds (Game Clock)
	Timer timer; // Used for gameDt (resets each frame)
	
	float gameClockSpeed = 0.0f; // != 0 (timeScale) --> Playing / == 0 --> Pause or Stop
	// Real Time Since Startup: seconds since game start (Real Time Clock) --> Engine.cpp
	// Real Time Delta Time: last frame time expressed in seconds (Real Time Clock) --> Engine.cpp
	// --------------------------------------------------
	
	

	JsonHandler jsonHandler;
};

#endif // __SCENE_MANAGER_H__