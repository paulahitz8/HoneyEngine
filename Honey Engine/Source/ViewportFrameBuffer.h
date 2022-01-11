#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>

class HoneyEngine;

class ViewportFrameBuffer : public Module
{
public:
	ViewportFrameBuffer(HoneyEngine* engine/*, bool start_enabled = true*/);
	~ViewportFrameBuffer();

	bool Start();
	bool PreUpdate(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();

public:
	uint frameBuffer = 0;
	uint renderBufferoutput = 0;
	uint texture = 0;
	bool show_viewport_window = true;

	HoneyEngine* engine = nullptr;
};