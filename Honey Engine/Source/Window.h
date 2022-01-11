#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class Window : public Module
{
public:

	Window(HoneyEngine* engine);

	// Destructor
	virtual ~Window();

	// Called before render is available
	bool Awake(Json configModule);

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* title);

	void AdjustBrightness(float brightness);
	float GetBrightness();

	// Retrive window size
	void GetWindowSize(uint& width, uint& height) const;
	int GetWidth() const;
	int GetHeight() const;
	bool GetFullscreen() const;
	bool GetFullscreenDesktop() const;
	bool GetResizable() const;
	bool GetBorderless() const;
	uint GetRefreshRate() const;
	const char* GetIcon() const;
	void SetFullscreen(bool fullscreen);
	void SetFullscreenDesktop(bool fullscreenDesktop);
	void SetResizable(bool resizable);
	void SetBorderless(bool borderless);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetIcon(const char* file);

	// Retrieve window scale
	uint GetScale() const;
	void GetPosition(int& x, int& y);

public:
	// The window we'll be rendering to
	SDL_Window* window;

	// The surface contained by the window
	SDL_Surface* screenSurface;

private:
	SString title;
	uint width;
	uint height;
	uint scale;
	float brightness;
	bool fullscreen = false;
	bool fullscreenDesktop = false;
	bool borderless = false;
	bool resizable = false;
	std::string iconFile;

	HoneyEngine* engine = nullptr;
};

#endif // __WINDOW_H__