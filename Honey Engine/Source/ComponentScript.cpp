#include "ComponentScript.h"
#include "GameObject.h"
#include "imgui_stdlib.h"
#include "PanelChooser.h"
#include "Engine.h"
#include "PanelAssets.h"
#include "FileSystem.h"
#include "PanelTextEditor.h"
#include "Editor.h"
#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ComponentScript::ComponentScript(GameObject* parent) : Component(parent)
{
	type = ComponentType::SCRIPT;
}

ComponentScript::~ComponentScript()
{
}

bool ComponentScript::Start()
{
	return true;
}

bool ComponentScript::Update()
{
	return true;
}

bool ComponentScript::InspectorDraw(PanelChooser* chooser)
{
	bool ret = true;

	// Inspector variables
	if (ImGui::CollapsingHeader(name.c_str()))
	{
		if (name == "TankMovement.lua")
		{
			ImGui::Text("name = Tank");
			ImGui::Text("position = { x, y, z }");
			ImGui::Text("speed = 2");
		}
		else if (name == "TurretMovement.lua")
		{
			ImGui::Text("name = Turret");
		}
		else if (name == "BulletMovement.lua")
		{
			ImGui::Text("name = Bullet");
			ImGui::Text("position = { x, y, z }");
			ImGui::Text("speed = 2");
		}
	}

	return ret;
}

