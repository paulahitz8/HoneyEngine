#include "PanelTextEditor.h"
#include "TextEditor.h"
#include <imgui.h>
#include "Editor.h"

PanelTextEditor::PanelTextEditor(Editor* editor)
{
	panelName = "TextEditor";
	this->editor = editor;
}

PanelTextEditor::~PanelTextEditor()
{
}

bool PanelTextEditor::Awake()
{
	editorBox.SetShowWhitespaces(false);
	editorBox.SetReadOnly(false);
	editorBox.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
	return true;
}

bool PanelTextEditor::PreUpdate()
{

	return true;
}

bool PanelTextEditor::Update()
{
	ImGui::Begin("Editor Window");
	if (ImGui::Button("Save LUA Script")) {
		savedText = editorBox.GetAllText();
		savedTextChar = savedText.c_str();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load LUA Script")) {
		if (savedTextChar != nullptr) {
			editorBox.InsertText(savedTextChar);
		}
	}
	ImGui::SameLine(ImGui::GetWindowWidth() - 60);
	if (ImGui::Button("Clear")) {
		editorBox.SelectAll();
		editorBox.Delete();
	}
	editorBox.Render("##EditorWindow");
	ImGui::End();

	return true;
}

bool PanelTextEditor::PostUpdate()
{
	return true;
}