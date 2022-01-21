#pragma once
#include "Component.h"
#include <filesystem>
#include "stb_image.h"

class ComponentScript : public Component
{
public:
	ComponentScript(GameObject* parent);
	~ComponentScript();
	bool Start();
	bool Update();

	bool InspectorDraw(PanelChooser* chooser);
};