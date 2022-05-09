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

	bool Init();
	void Run();
	void EngineCleanup();

private:
	void Logic(LogicElements& elements, Inputs& inputs, std::chrono::steady_clock& clock);
	void DrawFrame();

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
