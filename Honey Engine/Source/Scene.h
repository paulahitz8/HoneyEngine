#ifndef __SCENE_H__
#define __SCENE_H__

#include "GameObject.h"
#include "Importer.h"
#include "Engine.h"

#include <vector>

class Scene
{
public:
	Scene() : active(false)
	{
	}

	~Scene()
	{
		CleanUp();
	}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake()
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate(float dt)
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	GameObject* GetGameObject(int id)
	{
		for (GameObject* go : gameObjectList)
		{
			if (go->GetId() == id)
			{
				return go;
			}
		}

		return nullptr;
	}

	virtual GameObject* CreateEmptyGameObject(const char* name = nullptr)
	{
		GameObject* go = new GameObject(gameObjectList.size(), engine);
		this->gameObjectList.push_back(go);
		this->rootGo->AttachChild(go);

		return go;
	}

	virtual void DeleteGameObject(GameObject* gameObject)
	{
		for (std::vector<GameObject*>::iterator it = gameObjectList.begin(); it != gameObjectList.end(); ++it)
		{
			if ((*it)->GetId() == gameObject->GetId())
			{
				gameObjectList.erase(it);
				break;
			}
		}
		
		if (gameObject != nullptr)
		{
			GameObject* parent = gameObject->GetParent();
			std::vector<GameObject*> children = gameObject->GetChildren();
			if (children.size() > 0)
			{
				for (std::vector<GameObject*>::iterator ch = children.begin(); ch != children.end(); ch++)
				{
					GameObject* child = (*ch);
					GameObject* childParent = child->GetParent();
					childParent = gameObject->GetParent();
					parent->AttachChild(child);
				}
			}
			parent->RemoveChild(gameObject);

			gameObject->CleanUp();
			

			RELEASE(gameObject);
		}

	}

	void RemoveGameObjectIterator(std::vector<GameObject*>::iterator go)
	{
		GameObject* gameObject = (*go);
		if (gameObject != nullptr)
		{
			GameObject* parent = gameObject->GetParent();
			std::vector<GameObject*> children = gameObject->GetChildren();
			if (children.size() > 0)
			{
				for (std::vector<GameObject*>::iterator ch = children.begin(); ch != children.end(); ch++)
				{
					GameObject* child = (*ch);
					GameObject* childParent = child->GetParent();
					childParent = gameObject->GetParent();
					parent->AttachChild(child);
				}
			}
			parent->RemoveChild(gameObject);

			gameObjectList.erase(go);
			gameObject->CleanUp();
			RELEASE(gameObject);
		}
	}

public:
	SString name;
	bool active;

	HoneyEngine* engine = nullptr;
	std::vector<GameObject*> gameObjectList;
	GameObject* rootGo = nullptr;
	GameObject* currentCamera = nullptr;
};

#endif // __SCENE_H__