#include "Window.h"
#include "Engine.h"
#include "Defs.h"
#include "Log.h"
#include "ImGuiAppLog.h"

#include "SDL.h"

Window::Window(HoneyEngine* engine) : Module()
{
	window = NULL;
	screenSurface = NULL;
	name.Create("Window");
	this->engine = engine;
}

// Destructor
Window::~Window()
{
}

// Called before render is available
bool Window::Awake(Json configModule)
{
	CONSOLE_LOG("Init SDL window & surface");
	appLog->AddLog("Init SDL window & surface\n");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		CONSOLE_LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		appLog->AddLog("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		// Create window
		// L01: DONE 6: Load all required configurations from config.xml
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
		// Set up SDL to use OpenGL 2.x
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
		fullscreen = false;
		fullscreenDesktop = false;
		borderless = false;
		resizable = false;

		width = configModule.at("Width");
		height = configModule.at("Height");
		scale = configModule.at("Scale");

		if(fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN;
		if(borderless == true) flags |= SDL_WINDOW_BORDERLESS;
		if(resizable == true) flags |= SDL_WINDOW_RESIZABLE;
		if(fullscreenDesktop == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		if(window == NULL)
		{
			CONSOLE_LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			appLog->AddLog("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_assert(window != NULL);
			ret = false;
		}
		else
		{
			// Get window surface
			screenSurface = SDL_GetWindowSurface(window);
			//Get window brightness
			brightness = SDL_GetWindowBrightness(window);
			//Set window rezisable
			SetResizable(true);
			std::string iconFile = configModule.at("Icon");
			if (iconFile.size() > 1)
				SetIcon(iconFile.c_str());
		}
	}

	SetTitle(engine->GetTitle());

	return ret;
}

// Called before quitting
bool Window::CleanUp()
{
	CONSOLE_LOG("Destroying SDL window and quitting all SDL systems");
	appLog->AddLog("Destroying SDL window and quitting all SDL systems\n");

	// Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	// Quit SDL subsystems
	SDL_Quit();
	return true;
}

// Set new window title
void Window::SetTitle(const char* new_title)
{
	//title.create(new_title);
	SDL_SetWindowTitle(window, new_title);
}

void Window::AdjustBrightness(float brightness)
{
	brightness = brightness < 0 ? 0 : brightness;
	brightness = brightness > 1 ? 1 : brightness;

	SDL_SetWindowBrightness(window, brightness);
	this->brightness = SDL_GetWindowBrightness(window);
}

float Window::GetBrightness()
{
	return this->brightness;
}

void Window::GetWindowSize(uint& width, uint& height) const
{
	width = this->width;
	height = this->height;
}

int Window::GetWidth() const
{
	return (int)this->width;
}

int Window::GetHeight() const
{
	return (int)this->height;
}

bool Window::GetFullscreen() const
{
	return fullscreen;
}

bool Window::GetFullscreenDesktop() const
{
	return fullscreenDesktop;
}

bool Window::GetResizable() const
{
	return resizable;
}

bool Window::GetBorderless() const
{
	return borderless;
}

uint Window::GetRefreshRate() const
{
	uint ret = 0;

	SDL_DisplayMode displayMode;
	if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
		CONSOLE_LOG("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	else
		ret = displayMode.refresh_rate;
	return ret;
}

const char* Window::GetIcon() const
{
	return iconFile.c_str();
}

void Window::SetFullscreen(bool fullscreen)
{
	this->fullscreen = fullscreen;
	SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void Window::SetFullscreenDesktop(bool fullscreenDesktop)
{
	this->fullscreenDesktop = fullscreenDesktop;
	SDL_SetWindowFullscreen(window, fullscreenDesktop ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void Window::SetResizable(bool resizable)
{
	this->resizable = resizable;
	SDL_SetWindowResizable(window, (SDL_bool)resizable);
}

void Window::SetBorderless(bool borderless) 
{
	this->borderless = borderless;
	SDL_SetWindowBordered(window, (SDL_bool)!borderless);
}

void Window::SetWidth(int width)
{
	SDL_assert(width >= 0);
	this->width = (uint)width;
}

void Window::SetHeight(int height)
{
	SDL_assert(height >= 0);
	this->height = (uint)height;
}

void Window::SetIcon(const char* file)
{
	if (file != nullptr && file != iconFile)
	{
		iconFile = file;

		SDL_Surface* surface = SDL_LoadBMP(file);
		SDL_SetWindowIcon(window, surface);
		SDL_FreeSurface(surface);
	}
}

uint Window::GetScale() const
{
	return scale;
}

void Window::GetPosition(int& x, int& y)
{
	SDL_GetWindowPosition(window, &x, &y);
}