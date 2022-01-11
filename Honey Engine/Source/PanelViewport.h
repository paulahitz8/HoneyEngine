#pragma once
#include "Panel.h"

class Editor;
class HoneyEngine;

class PanelViewport : public Panel
{
public:
	PanelViewport(Editor* editor, HoneyEngine* engine);
	~PanelViewport();

	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();

private:
	Editor* editor = nullptr;
	HoneyEngine* engine = nullptr;
};
