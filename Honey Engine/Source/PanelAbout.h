#pragma once
#include "Panel.h"

class Editor;

class PanelAbout : public Panel
{
public:
	PanelAbout(Editor* editor);
	~PanelAbout();

	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();

	void ShowAboutWindow(bool* toggleAboutPanel);

private:
	Editor* editor = nullptr;
};
