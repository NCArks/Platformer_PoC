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

#include "test_map.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

#define ONE_LOGIC_FRAME std::chrono::microseconds(16666)

// Game logic thread's main function
void logic(LogicElements& elements, Inputs& inputs, std::chrono::steady_clock& clock) {
    std::vector<TileType> map_t = std::vector<TileType>();
    map_t.reserve(20000 * 200);
    fillMapTiles(map_t, 20000*200);
    elements.getMap() = Map(20000, 200, map_t);
    auto previous_time = clock.now();
    while (!elements.getShouldClose()) {
        auto current_time = clock.now();
        auto delta_time = current_time - previous_time;
        //std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(delta_time).count() << std::endl;
        int frames_passed = (int)(delta_time / ONE_LOGIC_FRAME);
        //std::cout << "number of frames: " << frames_passed << std::endl;
        if (frames_passed > 0) {
            previous_time += frames_passed * ONE_LOGIC_FRAME;
            for (int i = (int)inputs.getInputQueueSize(); i > 0; --i) {
                inputs.popQueue();
                inputs.clearStr();
                for (const auto key : inputs.getPressedKeys()) {
                    inputs.addStr(key);
                }
            }
            inputs.getPressedKeys();
            //elements.getMap();
            elements.getP1().PlayerUpdate(inputs.getPressedKeys(), frames_passed, elements.getMap());
            for (int i = 0; i < elements.getEnnemiACount(); i++) {
                elements.getEnnemiA(i).ennemiUpdate(frames_passed, elements.getMap());
            }
        }
        else {
            std::this_thread::sleep_until(previous_time + ONE_LOGIC_FRAME);
        }
    }
}

float aspect_ratio = 800.0f / 600.0f;
int window_height = 800;
int window_width = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    aspect_ratio = (float)width / (float)height;
    window_height = width;
    window_width = height;
}

int main(int argc, char** argv) {

    // Initialize GLFW
    if (!glfwInit()) {
        return 1;
    }

    // Create application window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Phantasy", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSwapInterval(1);

    // Load GLAD openGL
    bool err = gladLoadGL() == 0;
    if (err) {
        return 1;
    }

    // Load ImGui
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    // Create game elements
    LogicElements elements;
    DisplayElements display(elements);
    //PlayerDisplay pd1(elements.getP1());

    // Load game shaders
    Shader playerIcon;
    Shader mapTile;
    playerIcon.initialize("shaders/vertex.glsl", "shaders/fragment.glsl");
    mapTile.initialize("shaders/vertex.glsl", "shaders/tile.glsl");

    // Initialize GLFW inputs
    Inputs inputs;
    glfwSetKeyCallback(window, inputs.key_callback);

    // Initialize application clock
    std::chrono::steady_clock clock = std::chrono::steady_clock();

    // Start game logic thread
    std::thread t1(logic, std::ref(elements), std::ref(inputs), std::ref(clock));

    // Some display variables
    float zoom_level = 1.0f;
    float camera_x = 0.0f;
    bool scroll_right = true;

    // "Skill points system" variables
    float a = .0f;
    float b = .0f;
    float c = .0f;
    float d = .0f;

    // Main display loop
    while (!glfwWindowShouldClose(window)) {
        // Poll GLFW events
        glfwPollEvents();

        // Clear screen display
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Create new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow();
        {
            ImGui::Begin("debug info");

            ImGui::Text(("skill_points: " + std::to_string(100.0f - a - b - c - d)).c_str());
            ImGui::SliderFloat(std::string("a").c_str(), &a, .0f, 100 - b - c - d);
            ImGui::SliderFloat(std::string("b").c_str(), &b, .0f, 100 - a - c - d);
            ImGui::SliderFloat(std::string("c").c_str(), &c, .0f, 100 - a - b - d);
            ImGui::SliderFloat(std::string("d").c_str(), &d, .0f, 100 - a - b - c);

            ImGui::ColorEdit3("background color", (float*)&clear_color);

            ImGui::Text(("Keys: " + inputs.getPressedStr()).c_str());

            ImGui::Text(("state: " + elements.getP1().getState()).c_str());

            ImGui::Text(("pos_x: " + std::to_string(elements.getP1().getPosX())).c_str());
            ImGui::Text(("pos_y: " + std::to_string(elements.getP1().getPosY())).c_str());
            ImGui::Text(("spd_x: " + std::to_string(elements.getP1().getSpdX())).c_str());
            ImGui::Text(("spd_y: " + std::to_string(elements.getP1().getSpdY())).c_str());

            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::SliderFloat(std::string("walk_spd").c_str(), &elements.getP1().getRefWalkSpd(), .0f, 32.0f);
            ImGui::SliderFloat(std::string("jump_spd").c_str(), &elements.getP1().getRefJumpSpd(), .0f, 32.0f);
            ImGui::SliderFloat(std::string("gravity").c_str(), &elements.getP1().getRefGravityConst(), .0f, 32.0f);
            ImGui::SliderFloat(std::string("max_fall_spd").c_str(), &elements.getP1().getRefMaxFallSpd(), -32.0f, .0f);
            ImGui::SliderFloat(std::string("min_jump_spd").c_str(), &elements.getP1().getRefMinJumpSpd(), .0f, 32.0f);
            ImGui::SliderFloat(std::string("camera_x").c_str(), &camera_x, 0.0f, 20.0f);
            ImGui::SliderFloat(std::string("zoom").c_str(), &zoom_level, 1.0f, 50.0f);
            ImGui::End();
        }

        // Camera follows player
        if (scroll_right) {
            if (elements.getP1().getPosX() / TILE_SIZE - camera_x > zoom_level * .35f / aspect_ratio) {
                camera_x = elements.getP1().getPosX() / TILE_SIZE - zoom_level * .35f / aspect_ratio;
            }
            else if (elements.getP1().getPosX() / TILE_SIZE - camera_x < -zoom_level * .65f / aspect_ratio) {
                camera_x = elements.getP1().getPosX() / TILE_SIZE + zoom_level * .35f / aspect_ratio;
                scroll_right = false;
            }
        }
        else {
            if (elements.getP1().getPosX() / TILE_SIZE - camera_x > zoom_level * .65f / aspect_ratio) {
                camera_x = elements.getP1().getPosX() / TILE_SIZE - zoom_level * .35f / aspect_ratio;
                scroll_right = true;
            }
            else if (elements.getP1().getPosX() / TILE_SIZE - camera_x < -zoom_level * .35f / aspect_ratio) {
                camera_x = elements.getP1().getPosX() / TILE_SIZE + zoom_level * .35f / aspect_ratio;
            }
        }
        if (elements.getP1().getPosY() / TILE_SIZE > zoom_level * .95f) {
            zoom_level = elements.getP1().getPosY() / TILE_SIZE / .95f;
        }
        else if (elements.getP1().getPosY() / TILE_SIZE < -zoom_level * .95f) {
            zoom_level = -elements.getP1().getPosY() / TILE_SIZE / .95f;
        }

        //// Compute displayed space area
        int left_x = camera_x - zoom_level;
        int right_x = camera_x + zoom_level + 1;
        int bottom_y = 0;
        int up_y = 20;

        int y_min = max(bottom_y, 0);
        int y_max = min(up_y, 20);
        int x_min = max(left_x, 0);
        int x_max = min(right_x, elements.getMap().getMapWidth());

        // Draw map tiles
        mapTile.use();
        mapTile.setU("zoom", 1 / zoom_level);
        mapTile.setU("camera_x", camera_x);
        mapTile.setU("aspect_ratio", aspect_ratio);
        for (int y = y_min; y < y_max; y++) {
            for (int x = x_min; x < x_max; x++) {
                if (elements.getMap().isObstacle(x, y)) {
                    mapTile.setU("pos", x, y);
                    mapTile.setU("color", 0.8f, 0.8f, 0.8f);
                    display.getMapDisplay().bindDrawTile();
                }
                if (elements.getMap().getTile(x, y) == TileType::slope45d) {
                    mapTile.setU("pos", x, y);
                    mapTile.setU("color", 0.8f, 0.1f, 0.8f);
                    display.getMapDisplay().bindDrawDTile();
                }
                if (elements.getMap().getTile(x, y) == TileType::slope45b) {
                    mapTile.setU("pos", x, y);
                    mapTile.setU("color", 0.1f, 0.8f, 0.8f);
                    display.getMapDisplay().bindDrawBTile();
                }
            }
        }

        // Draw player
        playerIcon.use();
        playerIcon.setU("aspect_ratio", aspect_ratio);
        playerIcon.setU("pos", elements.getP1().getPosX() / TILE_SIZE, elements.getP1().getPosY() / TILE_SIZE);
        playerIcon.setU("zoom", 1 / zoom_level);
        playerIcon.setU("camera_x", camera_x);
        //playerIcon.setU("facing_left", elements.getP1().getFacingLeft());
        display.getPd1().bindDraw();

        // Draw ennemies A
        for (int i = 0; i < elements.getEnnemiACount(); i++) {
            playerIcon.use();
            playerIcon.setU("aspect_ratio", aspect_ratio);
            playerIcon.setU("pos", elements.getEnnemiA(i).getPosX() / TILE_SIZE, elements.getEnnemiA(i).getPosY() / TILE_SIZE);
            playerIcon.setU("zoom", 1 / zoom_level);
            playerIcon.setU("camera_x", camera_x);
            //playerIcon.setU("facing_left", elements.getP1().getFacingLeft());
            display.getPd1().bindDraw();
        }

        // Draw ImGui elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Close application
    elements.setShouldClose();
    t1.join();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
