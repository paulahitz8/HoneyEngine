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

	TextEditor editorBox;

private:

	std::string savedText;
	Editor* editor = nullptr;
};
