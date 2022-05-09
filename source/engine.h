#ifndef game_engine
#define game_engine

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "display_elements.h"
#include "inputs.h"
#include "logic_elements.h"
#include "shader.h"
#include "map.h"
#include "player.h"


#define ONE_LOGIC_FRAME std::chrono::microseconds(16666)

class engine
{
public:
	engine();
	~engine();

	/// <summary>
	/// Initializes all engine memory and pointers with correct values for a proper run. Needs to be run before the Run method is called.
	/// Starts the Game Logic Thread.
	/// </summary>
	/// <returns>True if completes properly, False otherwise</returns>
	bool Init();

	/// <summary>
	/// Runs the main loop of the game, mainly Draws. Logic is executed in a separate thread started in Init.
	/// </summary>
	void Run();

	/// <summary>
	/// Cleans all the memory, stops and join the game logic thread.
	/// </summary>
	void EngineCleanup();

private:

	/// <summary>
	/// Game Logic method executed in a separate thread. Updates the Game Data.
	/// </summary>
	/// <param name="elements">Logic Element object instance reference</param>
	/// <param name="inputs">Global Input object instance reference</param>
	/// <param name="clock">Steady Clock object instance reference</param>
	void Logic(LogicElements& elements, Inputs& inputs, std::chrono::steady_clock& clock);

	/// <summary>
	/// Draws data on the window based on engine memory updated by the Logic method. Uses OpenGL API, and ImGUI interface for display.
	/// Can be used to loop or check if the loop is flawed.
	/// </summary>
	/// <returns>False when an error happens, True otherwise</returns>
	bool DrawFrame();

	const char* glsl_version = "#version 130";
	const char* glsl_vertex_path = "shaders/vertex.glsl";
	const char* glsl_fragment_path = "shaders/fragment.glsl";
	const char* glsl_title_path = "shaders/tile.glsl";
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	PlayerSkills pskills;
	DisplayVariables dvar;
	std::unique_ptr<LogicElements> elements = nullptr;
	ImVec4 clear_color = {0.0f, 0.0f, 0.0f, 0.0f};
	GLFWwindow* window = nullptr;
	std::thread t1 = std::thread();
	std::unique_ptr<std::chrono::steady_clock> clock = nullptr;
	std::unique_ptr<Inputs> inputs = nullptr;
	std::unique_ptr<DisplayElements> display;
	Map* map = nullptr;
	Player* player = nullptr;;
	Shader playerIcon;
	Shader mapTile;

};

#endif // !game_engine
