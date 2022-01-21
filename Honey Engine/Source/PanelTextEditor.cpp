#include "PanelTextEditor.h"
#include "TextEditor.h"
#include "Editor.h"
#include "FileSystem.h"
#include "PanelAssets.h"
#include "ComponentScript.h"
#include "SceneManager.h"
#include "PanelInspector.h"
#include "Engine.h"
#include <imgui.h>
#include "Editor.h"

PanelTextEditor::PanelTextEditor(Editor* editor)
{
	panelName = "TextEditor";
	this->editor = editor;
}

PanelTextEditor::~PanelTextEditor() {}

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
	if (ImGui::Button("Save"))
	{
		savedText = editorBox.GetAllText();
		//savedTextChar = savedText.c_str();
		editor->engine->GetFileSystem()->SaveFile(editor->GetPanelAssets()->scriptPath.c_str(), savedText);
	}
	ImGui::SameLine();
	if (ImGui::Button("Attach"))
	{
		if (!editor->GetPanelInspector()->hasScript)
		{
			editor->engine->GetSceneManager()->GetCurrentScene()->GetGameObject(editor->panelGameObjectInfo.selectedGameObjectID)->CreateComponent<ComponentScript>();
		}
	}
	ImGui::SameLine(ImGui::GetWindowWidth() - 60);
	if (ImGui::Button("Clear"))
	{
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