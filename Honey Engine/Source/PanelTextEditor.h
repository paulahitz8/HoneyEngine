#pragma once
#include "Panel.h"
#include "TextEditor.h"

class Editor;

class PanelTextEditor : public Panel
{
public:

	PanelTextEditor(Editor* editor);
	~PanelTextEditor();

	bool Awake();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();

private:

	TextEditor editorBox;
	std::string savedText;
	const char* savedTextChar;
	char* savedNoConstTextChar;
	Editor* editor = nullptr;
};
