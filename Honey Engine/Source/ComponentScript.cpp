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
	//name = owner->GetEngine()->GetEditor()->GetPanelAssets()->scriptName;
	return true;
}

bool ComponentScript::InspectorDraw(PanelChooser* chooser)
{
	bool ret = true;

	if (ImGui::CollapsingHeader(name.c_str()))
	{
		// inspector variables
	}

	return ret;
}

