#include "Lua.h"
#include "Engine.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "ImGuiAppLog.h"
#include "Log.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Input.h"

bool LuaWork::isTest;
bool LuaWork::isMovingX;
bool LuaWork::isMovingZ;
float LuaWork::xPos;
float LuaWork::zPos;
std::string LuaWork::nameInLua;

struct GO
{
	float posx, posz;
}go;

LuaWork::LuaWork(HoneyEngine* engine)
{
	this->engine = engine;
}

int LuaWork::Test(lua_State* L)
{
	if (lua_isstring(L, 1))
	{
		nameInLua = lua_tostring(L, 1);
		isTest = true;
		//lua_pushnumber(L, 1);
	}
	return 1;
}

int LuaWork::Test2()
{
	try
	{
			std::string goName = nameInLua;
			std::vector<GameObject*>::iterator item = engine->GetSceneManager()->GetCurrentScene()->gameObjectList.begin();
			while (item != engine->GetSceneManager()->GetCurrentScene()->gameObjectList.end())
			{
				if ((*item)->name.compare(goName) == 0)
				{
					if ((*item)->GetTransform() != nullptr)
					{
						xPos = (*item)->GetTransform()->GetPosition().x;
						zPos = (*item)->GetTransform()->GetPosition().z;

						//(*item)->GetTransform()->SetPosition({go.posx, (*item)->GetTransform()->GetPosition().y, go.posz});

						return 1;
					}
				}
				item++;
			}
	}
	catch(...)
	{
		CONSOLE_LOG("Couldn't find any gameObject with this name\n");
		appLog->AddLog("Couldn't find any gameObject with this name\n");
	}
	return 1;
}

int LuaWork::MoveX(lua_State* L)
{
	if (lua_isnumber(L, 1))
	{
		go.posx = lua_tonumber(L, 1);
		isMovingX = true;
		//lua_pushnumber(L, 1);
	}
	return 1;
}

int LuaWork::MoveZ(lua_State* L)
{
	if (lua_isnumber(L, 1))
	{
		go.posz = lua_tonumber(L, 1);
		isMovingZ = true;
		//lua_pushnumber(L, 1);
	}
	return 1;
}

int LuaWork::Moving()
{
	try
	{
		std::string goName = nameInLua;
		std::vector<GameObject*>::iterator item = engine->GetSceneManager()->GetCurrentScene()->gameObjectList.begin();
		while (item != engine->GetSceneManager()->GetCurrentScene()->gameObjectList.end())
		{
			if ((*item)->name.compare(goName) == 0)
			{
				if ((*item)->GetTransform() != nullptr)
				{
					//if(is)
					(*item)->GetTransform()->SetPosition({ go.posx, (*item)->GetTransform()->GetPosition().y, go.posz });

					return 1;
				}
			}
			item++;
		}
	}
	catch (...)
	{
		CONSOLE_LOG("Couldn't find any gameObject with this name\n");
		appLog->AddLog("Couldn't find any gameObject with this name\n");
	}
	return 1;
}

Lua::Lua(HoneyEngine* engine)
{
	this->engine = engine;
	luaWork = new LuaWork(engine);
	L = luaL_newstate();
	
	luaL_openlibs(L);
	lua_register(L, "test", &LuaWork::Test);
	lua_register(L, "moveX", &LuaWork::MoveX);
	lua_register(L, "moveZ", &LuaWork::MoveZ);
		
	if (CheckLua(L, luaL_dofile(L, "Assets/Scripts/Test.lua")))
	{

		lua_getglobal(L, "Movement");
		if (lua_isfunction(L, -1))
		{
			const char* key = "F";
			if (engine->GetInput()->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
			{
				key = "I";
			}
			if (engine->GetInput()->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
			{
				key = "K";
			}
			if (engine->GetInput()->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
			{
				key = "J";
			}
			if (engine->GetInput()->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
			{
				key = "L";
			}
			else
			{
				key = "F";
			}
			lua_pushnumber(L, luaWork->xPos);
			lua_pushnumber(L, luaWork->zPos);
			lua_pushstring(L, key);
			if (CheckLua(L, lua_pcall(L, 3, 2, 0)))
			{
				if (lua_istable(L, -2))
				{
					lua_pushstring(L, "x");
					lua_gettable(L, -3);
					go.posx = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "z");
					lua_gettable(L, -3);
					go.posz = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);
					std::cout << "the position is x:  " << go.posx << "  z:  " << go.posz << std::endl;
				}	
			}
		}
	}
	else
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
	}

}

Lua::~Lua()
{
	if (L)
	{
		lua_close(L);
	}
}

bool Lua::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

//int lua_FindGOWithName(lua_State* L)
//{
//	//try
//	//{
//		//if (lua_isstring(L, 1))
//		//{
//			//std::string goName = lua_tostring(L, 1);
//			//std::vector<GameObject*>::iterator item = engine->GetSceneManager()->currentScene->gameObjectList.begin();
//			//while (item != engine->GetSceneManager()->currentScene->gameObjectList.end())
//			//{
//			//	if ((*item)->name.compare(goName))
//			//	{
//			//		if ((*item)->GetTransform() != nullptr)
//			//		{
//			//			int c = (*item)->GetTransform()->GetPosition().x;
//			//			//return (*item)->GetTransform();
//			//			lua_pushnumber(L, c);
//			//			return 1;
//			//		}
//			//	}
//			//	item++;
//			//}
//		//}
//	//}
//	/*catch(...)
//	{
//		CONSOLE_LOG("Couldn't find any gameObject with this name\n");
//		appLog->AddLog("Couldn't find any gameObject with this name\n");
//	}*/
//
//			int c = 1;
//			//return (*item)->GetTransform();
//			lua_pushnumber(L, c);
//	return 1;
//}

//int lua_HostFunction(lua_State* L)
//{
//	float a = (float)lua_tonumber(L, 1);
//	float b = (float)lua_tonumber(L, 2);
//	std::cout << "[CPP S4] HostFunction(" << a << ", " << b << ") called from Lua" << std::endl;
//	float c = a * b;
//	lua_pushnumber(L, c);
//	return 1;
//}

//bool KindaStart()
//{
//
//}
