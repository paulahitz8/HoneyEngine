# HoneyEngine

A simple 3D game engine.

![logo](https://github.com/paulahitz8/HoneyEngine/blob/main/Honey%20Engine/Honey/Assets/Icons/honeyengine_logo.png?raw=true)

## Description

HoneyEngine is a game engine created for our class "Game Engines" in our Video Game Design and Development Degree in CITM (UPC).
For this last delivery we implemented scripting with LUA, a simple programming language that will manage our scripts. We implemented
a communication method between the engine (C++) and the scripts (LUA), as well as an in-game text editor where the user can edit the
scripts and attach them to game objects. Check below the TUTORIAL to know which steps to take to check this out.

Thank you to Alex Ávila and Bosco Barber for letting us use their Ko-Fi Engine as a base for the last delivery. :) 
## Developers

- Paula Hitz (https://github.com/paulahitz8)
- Irene Hernández (https://github.com/ihedud)
- María Calle (https://github.com/mav006)

## Tutorial
In order to activate the scripts follow these steps:
- Select game object to add script
	- In this delivery the Tank would have the Tank Movement script and the Turret would have the Turret Movement script
- In the assets folder, navigate to the scripts
- Double click any script to see it in the text editor panel
- Here you can read, edit, clear or attach the script
- Click attach (with the game object selected), to attach the script
- Click play and test it out!

*We include a video [tutorial](https://github.com/paulahitz8/HoneyEngine/tree/main/Honey%20Engine/Honey/Assets/Tutorial) for clarification*

## Features

*NEW!*
- Scripting with LUA
	- Tank movement
	- Turret movement
	- Bullet movement

- Drag and drop of models (fbx) and textures (png or jpg)
- Game objects with mesh, texture and transform components
- ImGui UI: console, configuration, hierarchy, inspector, about, and demo windows
- Unity-like camera controls
- Save and load

## Controls 

Tank Movement
- WASD to move tank around
- Mouse movement to move turret around
- SPACE to shoot bullets

Camera Movement
- CTRL + WASDQE to move camera
- CTRL + Mouse wheel to zoom in and out
- Right click camera rotation
- Alt+Left click to orbit around game object
- CTRL + F to focus in game object
- SHIFT to increase camera speed


General Controls
- ESC to quit

## Bugs
- One of the bugs we encountered was that the bullet does not have any texture.
- For the panel inspector, where we wanted to display the variables of the LUA scripts, we did not find any way to get them. For the future, we would like to investigate furthermore to fix this issue.

## License

This project is licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.
