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

	static int Test(lua_State* ptrState);
	int Test2();
	static int MoveX(lua_State* ptrState);
	static int MoveZ(lua_State* ptrState);
	int Moving();
	

private:
	static SceneManager* instance;
	static std::string nameInLua;
	HoneyEngine* engine;
	static float xPos;
	static float zPos;
	static bool isTest;
	static bool isMovingX;
	static bool isMovingZ;
	bool isTest2 = false;
};

class Lua
{
public:
	Lua(HoneyEngine* engine);
	~Lua();

	bool CheckLua(lua_State* L, int r);
	//int lua_FindGOWithName(lua_State* ptrState);
	//bool KindaStart();

	LuaWork* luaWork = nullptr;

private:
	lua_State* L;
	HoneyEngine* engine;
};

