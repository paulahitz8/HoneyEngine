#pragma once
#ifndef SCENE_INTRO_H
#define SCENE_INTRO_H

#include "Scene.h"
//#include "Globals.h"
#include "JsonHandler.h"

#define MAX_SNAKE 2

class GameObject;
class Lua;
class LuaWork;

class SceneIntro : public Scene
{
public:
	SceneIntro(HoneyEngine* engine);
	~SceneIntro();

	bool Start();
	bool PreUpdate(float dt);
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

	//bool bulletRot = false;

private:
	int random = 0;
	JsonHandler jsonHandler;
	Json j;

	// Temporal to manage the use of the camera
	GameObject* camera = nullptr;
	Lua* lua = nullptr;

};

#endif SCENE_INTRO_H // SCENE_INTRO_H