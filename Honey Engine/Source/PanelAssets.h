#pragma once
#include "Panel.h"
#include <filesystem>
#include "stb_image.h"

class Editor;
struct TextureIcon
{
	unsigned int id = 0;
	int width, height, nrChannels;
};

class PanelAssets : public Panel
{
public:
	PanelAssets(Editor* editor);
	~PanelAssets();
	bool Start();
	bool Update();
	bool PostUpdate();

	//Temp Function to load file and directory icons
	void LoadIcons(TextureIcon& texture,const char* path);
	std::string scriptPath;
	std::string scriptName;

private:
	Editor* editor = nullptr;
	TextureIcon fileTexture;
	TextureIcon directoryTexture;
	std::string fileIcon, directoryIcon;
	const std::filesystem::path assetsDir = "Assets";
	std::filesystem::path currentDir = "Assets";
};