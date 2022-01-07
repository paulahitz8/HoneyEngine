#pragma once
#include "Panel.h"

class Editor;
class KoFiEngine;

class PanelViewport : public Panel
{
public:
	PanelViewport(Editor* editor, KoFiEngine* engine);
	~PanelViewport();

	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();

private:
	Editor* editor = nullptr;
	KoFiEngine* engine = nullptr;
};
