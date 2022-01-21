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
#include "Window.h"
#include "ComponentMaterial.h"

bool LuaWork::isName;
float LuaWork::xPos;
float LuaWork::zPos;
float LuaWork::yRot;
float LuaWork::xBulletPos;
float LuaWork::yBulletPos;
float LuaWork::zBulletPos;
float LuaWork::yBulletRot;
float LuaWork::yTurretRot;
float LuaWork::mouseRot;
std::string LuaWork::tankNameInLua;
std::string LuaWork::bulletNameInLua;
std::string LuaWork::turretNameInLua;

void LuaWork::CreateBullet()
{
	std::string bulletName = bulletNameInLua;
	std::vector<GameObject*>::iterator item = engine->GetSceneManager()->GetCurrentScene()->gameObjectList.begin();
	while (item != engine->GetSceneManager()->GetCurrentScene()->gameObjectList.end())
	{
		if ((*item)->name.compare(bulletName) == 0)
		{
			bulletExists = true;
		}
		item++;
	}
	if (!bulletExists)
	{
		GameObject* bullet = Importer::GetInstance()->ImportModel("Assets/Models/Shell.fbx");
		bullet->SetName("Bullet");
		bullet->CreateComponent<ComponentMaterial>();
		engine->GetSceneManager()->GetCurrentScene()->bulletRot = true;
		//bullet->GetComponent<ComponentMaterial>()->LoadTexture("Assets/Textures/silver.png");
	}
}

LuaWork::LuaWork(HoneyEngine* engine)
{
	this->engine = engine;
}

int LuaWork::FindTankName(lua_State* L)
{
	if (lua_isstring(L, 1))
	{
		tankNameInLua = lua_tostring(L, 1);
		isName = true;
	}
	return 1;
}

int LuaWork::FindBulletName(lua_State* L)
{
	if (lua_isstring(L, 1))
	{
		bulletNameInLua = lua_tostring(L, 1);
		isName = true;
	}
	return 1;
}

int LuaWork::FindTurretName(lua_State* L)
{
	if (lua_isstring(L, 1))
	{
		turretNameInLua = lua_tostring(L, 1);
		isName = true;
	}
	return 1;
}

int LuaWork::GetPosFromGOName()
{
	try
	{
			std::string goName = tankNameInLua;
			std::string bulletName = bulletNameInLua;
			std::string turretName = turretNameInLua;
			std::vector<GameObject*>::iterator item = engine->GetSceneManager()->GetCurrentScene()->gameObjectList.begin();
			while (item != engine->GetSceneManager()->GetCurrentScene()->gameObjectList.end())
			{
				if ((*item)->name.compare(goName) == 0)
				{
					if ((*item)->GetTransform() != nullptr)
					{
						xPos = (*item)->GetTransform()->GetPosition().x;
						zPos = (*item)->GetTransform()->GetPosition().z;
						yRot = (*item)->GetTransform()->GetRotation().y;
					}
				}
				else if ((*item)->name.compare(bulletName) == 0)
				{
					if ((*item)->GetTransform() != nullptr)
					{
						xBulletPos = (*item)->GetTransform()->GetPosition().x;
						yBulletPos = (*item)->GetTransform()->GetPosition().y;
						zBulletPos = (*item)->GetTransform()->GetPosition().z;
						yBulletRot = (*item)->GetTransform()->GetRotation().y;
					}
				}
				else if ((*item)->name.compare(turretName) == 0)
				{
					if ((*item)->GetTransform() != nullptr)
					{
						yTurretRot = (*item)->GetTransform()->GetRotation().y;
					}
				}
				item++;
			}
			return 1;
	}
	catch(...)
	{
		CONSOLE_LOG("Couldn't find any gameObject with this name\n");
		appLog->AddLog("Couldn't find any gameObject with this name\n");
	}
	return 1;
}

int LuaWork::SetPosFromGONameTank(float posx, float posz, float roty)
{
	try
	{
		std::string goName = tankNameInLua;
		std::string turretName = turretNameInLua;
		std::vector<GameObject*>::iterator item = engine->GetSceneManager()->GetCurrentScene()->gameObjectList.begin();
		while (item != engine->GetSceneManager()->GetCurrentScene()->gameObjectList.end())
		{
			if ((*item)->name.compare(goName) == 0)
			{
				if ((*item)->GetTransform() != nullptr)
				{
					if((*item)->GetTransform()->GetPosition().x != posx)
					{
						(*item)->GetTransform()->SetPosition({ posx, (*item)->GetTransform()->GetPosition().y, (*item)->GetTransform()->GetPosition().z });
					}
					if ((*item)->GetTransform()->GetPosition().z != posz)
					{
						(*item)->GetTransform()->SetPosition({ (*item)->GetTransform()->GetPosition().x, (*item)->GetTransform()->GetPosition().y, posz });
					}
					if ((*item)->GetTransform()->GetRotation().y != roty)
					{
						(*item)->GetTransform()->SetRotation({ (*item)->GetTransform()->GetRotation().x, roty, (*item)->GetTransform()->GetRotation().z });
					}
					
				}
			}
			else if ((*item)->name.compare(turretName) == 0)
			{
				if ((*item)->GetTransform() != nullptr)
				{
					(*item)->GetTransform()->SetRotation({ (*item)->GetTransform()->GetRotation().x, -mouseRot * 0.005f, (*item)->GetTransform()->GetRotation().z });
				}
			}
			item++;
		}
		return 1;
	}
	catch (...)
	{
		CONSOLE_LOG("Couldn't find any gameObject with this name\n");
		appLog->AddLog("Couldn't find any gameObject with this name\n");
	}
	return 1;
}

int LuaWork::SetPosFromGONameBullet(float posx, float posz, float posy)
{
	try
	{
		std::string bulletName = bulletNameInLua;
		std::vector<GameObject*>::iterator item = engine->GetSceneManager()->GetCurrentScene()->gameObjectList.begin();
		while (item != engine->GetSceneManager()->GetCurrentScene()->gameObjectList.end())
		{
			if ((*item)->name.compare(bulletName) == 0)
			{
				if ((*item)->GetTransform() != nullptr)
				{
					if ((*item)->GetTransform()->GetPosition().x != posx);
					{
						(*item)->GetTransform()->SetPosition({ posx, (*item)->GetTransform()->GetPosition().y, (*item)->GetTransform()->GetPosition().z });
					}
					if ((*item)->GetTransform()->GetPosition().y != posy);
					{
						(*item)->GetTransform()->SetPosition({ (*item)->GetTransform()->GetPosition().x, posy, (*item)->GetTransform()->GetPosition().z });
					}
					if ((*item)->GetTransform()->GetPosition().z != posz);
					{
						(*item)->GetTransform()->SetPosition({ (*item)->GetTransform()->GetPosition().x, (*item)->GetTransform()->GetPosition().y, posz });
					}
					if (engine->GetSceneManager()->GetCurrentScene()->bulletRot)
					{
						(*item)->GetTransform()->SetRotation({ (*item)->GetTransform()->GetRotation().x, yTurretRot - yRot, (*item)->GetTransform()->GetRotation().z });
						engine->GetSceneManager()->GetCurrentScene()->bulletRot = false;
					}
				}
			}
			item++;
		}
		return 1;
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
	lua_register(L, "FindTurretName", &LuaWork::FindTurretName);
	lua_register(L, "FindBulletName", &LuaWork::FindBulletName);
	lua_register(L, "FindTankName", &LuaWork::FindTankName);
	
	// Tank Movement
	if (CheckLua(L, luaL_dofile(L, "Assets/Scripts/TankMovement.lua")))
	{
		lua_getglobal(L, "TankMovement");
		if (lua_isfunction(L, -1))
		{
			const char* key = "F";
			if (engine->GetInput()->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				key = "NW";
			}
			else if (engine->GetInput()->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				key = "NE";
			}
			else if (engine->GetInput()->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				key = "SW";
			}
			else if (engine->GetInput()->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && engine->GetInput()->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				key = "SE";
			}
			else if (engine->GetInput()->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				key = "N";
			}
			else if (engine->GetInput()->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				key = "W";
			}
			else if (engine->GetInput()->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				key = "S";
			}
			else if (engine->GetInput()->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				key = "E";
			}

			lua_pushnumber(L, luaWork->xPos);
			lua_pushnumber(L, luaWork->zPos);
			lua_pushstring(L, key);
			lua_pushnumber(L, luaWork->yRot);
			
			if (CheckLua(L, lua_pcall(L, 4, 3, 0)))
			{
				if (lua_istable(L, -3))
				{
					lua_pushstring(L, "x");
					lua_gettable(L, -4);
					luaWork->xPos = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "z");
					lua_gettable(L, -4);
					luaWork->zPos = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "y");
					lua_gettable(L, -4);
					luaWork->yRot = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);
				}	
			}
		}

		lua_getglobal(L, "TurretRotation");
		if (lua_isfunction(L, -1))
		{
			float width = engine->GetWindow()->GetWidth();
			float mouseX = engine->GetInput()->GetMouseX();
			lua_pushnumber(L, width);
			lua_pushnumber(L, mouseX);
			if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
			{
				luaWork->mouseRot = (float)lua_tonumber(L, -1);
			}
		}

		luaWork->SetPosFromGONameTank(luaWork->xPos, luaWork->zPos, luaWork->yRot);
	}
	else
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
	}

	// Bullet Movement

	if (CheckLua(L, luaL_dofile(L, "Assets/Scripts/BulletMovement.lua")))
	{
		//luaWork->yBulletRot -= luaWork->yRot;
		luaWork->SetPosFromGONameBullet(luaWork->xBulletPos, luaWork->zBulletPos, luaWork->yBulletPos);
		lua_getglobal(L, "BulletMovement");
		if (lua_isfunction(L, -1))
		{
			lua_pushnumber(L, luaWork->xBulletPos);
			lua_pushnumber(L, luaWork->yBulletPos);
			lua_pushnumber(L, luaWork->zBulletPos);
			lua_pushnumber(L, luaWork->yBulletRot);
			//std::cout << luaWork->yBulletRot << std::endl;
			if (CheckLua(L, lua_pcall(L, 4, 3, 0)))
			{
				if (lua_istable(L, -3))
				{
					lua_pushstring(L, "x");
					lua_gettable(L, -4);
					luaWork->xBulletPos = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "z");
					lua_gettable(L, -4);
					luaWork->zBulletPos = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);

					lua_pushstring(L, "y");
					lua_gettable(L, -4);
					luaWork->yBulletPos = (float)lua_tonumber(L, -1);
					lua_pop(L, 1);

					std::cout << "bullet script working" << std::endl;
					//std::cout << "the position is x:  " << luaWork->xBulletPos << "  y: " << luaWork->yBulletPos << "   z:  " << luaWork->zBulletPos << std::endl;
					luaWork->SetPosFromGONameBullet(luaWork->xBulletPos, luaWork->zBulletPos, luaWork->yBulletPos);
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