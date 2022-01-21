#include "ComponentScript.h"
#include "GameObject.h"
#include "imgui_stdlib.h"
#include "PanelChooser.h"
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
	LoadIcons(fileTexture, fileIcon.c_str());
	LoadIcons(directoryTexture, directoryIcon.c_str());
	return true;
}

bool ComponentScript::Update()
{
	float padding = 16.0f;
	float iconSize = 96.0f;
	float cellSize = iconSize + padding;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	if (ImGui::CollapsingHeader("New Script"))
	{
		ImGui::Begin("Scripts");
		//ImGui::Columns(columnCount, 0, false);
		//Back button when we enter on a folder, however we dont want it to go further back if we are on the assets folder or the
		//user could access system files which is not right
		if (currentDir != std::filesystem::path(assetsDir)) {
			if (ImGui::Button("<-")) {
				//setting current directory to its parent (the one before)
				currentDir = currentDir.parent_path();
			}
		}
		for (auto& directoryEntry : std::filesystem::directory_iterator(currentDir)) {
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, assetsDir);
			std::string filenameString = relativePath.filename().string();

			uint id = directoryEntry.is_directory() ? directoryTexture.id : fileTexture.id;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)id, { iconSize,iconSize });
			ImGui::PopStyleColor();

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
				if (directoryEntry.is_directory())
					currentDir /= path.filename();

			}

			ImGui::TextWrapped(filenameString.c_str());
			//ImGui::NextColumn();
		}
		//ImGui::Columns(1);
		ImGui::End();
	}


	return true;
}

bool ComponentScript::InspectorDraw(PanelChooser* chooser)
{
	bool ret = true;

	//if (ImGui::CollapsingHeader("Scripts")) {
	//	ImGui::Text("Name:");
	//	ImGui::SameLine();
	//	ImGui::InputText("##Name", &(owner->name));
	//	ImGui::Checkbox("Active", &owner->active);
	//}

	return ret;
}

void ComponentScript::LoadIcons(TextureIcon& texture, const char* path)
{
	unsigned char* pixels = stbi_load(path, &texture.width, &texture.height, &texture.nrChannels, STBI_rgb_alpha);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (pixels)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(pixels);
}
