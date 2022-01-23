#pragma once
#include <string>
#include <iostream>

extern "C"
{
#include "..\Honey\Lua\include\lua.h"
#include "..\Honey\Lua\include\lauxlib.h"
#include "..\Honey\Lua\include\lualib.h"
#include "..\Honey\Lua\include\lua.hpp"
}

#ifdef _WIN32
#pragma comment(lib, "Honey/Lua/liblua54.a")
#endif

class HoneyEngine;
class ComponentTransform;
class SceneManager;

class LuaWork
{
	friend class SceneIntro;
	friend class Lua;
public:
	LuaWork(HoneyEngine* engine);
	~LuaWork();

	static int FindTankName(lua_State* ptrState);
	static int FindTurretName(lua_State* ptrState);
	static int FindBulletName(lua_State* ptrState);
	int GetPosCScript();
	int SetPosCScript(float posx, float posz, float roty);
	int SetPosCScriptBullet(float posx, float posz, float posy);
	void CreateBullet();

private:
	HoneyEngine* engine;
	static float xPos;
	static float zPos;
	static float yRot;
	static float xBulletPos;
	static float yBulletPos;
	static float zBulletPos;
	static float yBulletRot;
	static float yTurretRot;
	static float mouseRot;
	bool bulletExists = false;
};

class Lua
{
public:
	Lua(HoneyEngine* engine);
	~Lua();

	bool CheckLua(lua_State* L, int r);
	LuaWork* luaWork = nullptr;

private:
	lua_State* L;
	HoneyEngine* engine;
};

