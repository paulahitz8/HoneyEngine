#pragma once
#include "Panel.h"

class Editor;
class HoneyEngine;

class PanelRuntimeState : public Panel
{
public:
	PanelRuntimeState(Editor* editor, HoneyEngine* engine);
	~PanelRuntimeState();

	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();

	void DrawRuntimePanel();

private:
	Editor* editor = nullptr;
	HoneyEngine* engine = nullptr;
};
