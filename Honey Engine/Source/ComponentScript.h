#pragma once
#include "Component.h"
#include <filesystem>
#include "stb_image.h"

struct TextureIcon {
	unsigned int id = 0;
	int width, height, nrChannels;
};

class ComponentScript : public Component
{
public:
	ComponentScript(GameObject* parent);
	~ComponentScript();
	bool Start();
	bool Update();

	bool InspectorDraw(PanelChooser* chooser);

	void LoadIcons(TextureIcon& texture, const char* path);

private:

	TextureIcon fileTexture;
	TextureIcon directoryTexture;
	std::string fileIcon, directoryIcon;
	const std::filesystem::path assetsDir = "Library";
	std::filesystem::path currentDir = "Library";

};