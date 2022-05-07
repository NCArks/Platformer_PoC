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
void logic(LogicElements* elements, Inputs& inputs, std::chrono::steady_clock& clock) {
    Map m = *elements->getMap();
    auto previous_time = clock.now();
    while (!elements->getShouldClose()) {
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

            elements->getP1()->PlayerUpdate(inputs.getPressedKeys(), frames_passed, m);

            NpcGoomba* g;
            for (int i = 0; i < elements->getEnnemiACount(); i++) {
                g = elements->getEnnemiA(i);
                g->ennemiUpdate(frames_passed,m);
            }
        }
        else {
            std::this_thread::sleep_until(previous_time + ONE_LOGIC_FRAME);
        }
    }
}

float aspect_ratio = 800.0f / 600.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    aspect_ratio = (float)width / (float)height;
}

int main(int argc, char** argv) {
    //if (true) {
    //    LogicElements elts;
    //    elts.getMap() = Map(10, 10, map_tiles);
    //    elts.getP1().setPos(1.6f, 4.4f);
    //    elts.getP1().setSpd(2.0f, -0.145f);
    //    std::cout << "b:" << elts.getP1().getPosX() << " " << elts.getP1().getPosY() << std::endl;
    //    elts.getP1().updatePhysics(1.0f, elts.getMap());
    //    std::cout << "a:" << elts.getP1().getPosX() << " " << elts.getP1().getPosY() << std::endl;
    //    return 0;
    //}

    // Initialize GLFW
    if (!glfwInit()) {
        return 1;
    }
    const char* glsl_version = "#version 130";

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
    LogicElements* elements = new LogicElements();;
    elements->setEnnemiA(1);
    Map* m = new Map(10, 10, map_tiles);
    elements->setMap(m);
    DisplayElements display(elements);
    Player* p = elements->getP1();
    //PlayerDisplay pd1(elements.getP1());
    NpcGoomba* goomba = elements->getEnnemiA(1);

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
    std::thread t1(logic, elements, std::ref(inputs), std::ref(clock));

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

            ImGui::Text(("state: " + p->getState()).c_str());

            ImGui::Text(("pos_x: " + std::to_string(p->getPosX())).c_str());
            ImGui::Text(("pos_y: " + std::to_string(p->getPosY())).c_str());
            ImGui::Text(("spd_x: " + std::to_string(p->getSpdX())).c_str());
            ImGui::Text(("spd_y: " + std::to_string(p->getSpdY())).c_str());

            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::SliderFloat(std::string("walk_spd").c_str(), &(p->getRefWalkSpd()), .0f, 32.0f);
            ImGui::SliderFloat(std::string("jump_spd").c_str(), &(p->getRefJumpSpd()), .0f, 32.0f);
            ImGui::SliderFloat(std::string("gravity").c_str(), &(p->getRefGravityConst()), .0f, 32.0f);
            ImGui::SliderFloat(std::string("max_fall_spd").c_str(), &(p->getRefMaxFallSpd()), -32.0f, .0f);
            ImGui::SliderFloat(std::string("min_jump_spd").c_str(), &(p->getRefMinJumpSpd()), .0f, 32.0f);
            ImGui::SliderFloat(std::string("camera_x").c_str(), &camera_x, 0.0f, 20.0f);
            ImGui::SliderFloat(std::string("zoom").c_str(), &zoom_level, 1.0f, 50.0f);
            ImGui::End();
        }

        // Camera follows player
        if (scroll_right) {
            if (p->getPosX() / TILE_SIZE - camera_x > zoom_level * .35f / aspect_ratio) {
                camera_x = elements->getP1()->getPosX() / TILE_SIZE - zoom_level * .35f / aspect_ratio;
            }
            else if (elements->getP1()->getPosX() / TILE_SIZE - camera_x < -zoom_level * .65f / aspect_ratio) {
                camera_x = elements->getP1()->getPosX() / TILE_SIZE + zoom_level * .35f / aspect_ratio;
                scroll_right = false;
            }
        }
        else {
            if (p->getPosX() / TILE_SIZE - camera_x > zoom_level * .65f / aspect_ratio) {
                camera_x = p->getPosX() / TILE_SIZE - zoom_level * .35f / aspect_ratio;
                scroll_right = true;
            }
            else if (p->getPosX() / TILE_SIZE - camera_x < -zoom_level * .35f / aspect_ratio) {
                camera_x = p->getPosX() / TILE_SIZE + zoom_level * .35f / aspect_ratio;
            }
        }
        if (p->getPosY() / TILE_SIZE > zoom_level * .95f) {
            zoom_level = p->getPosY() / TILE_SIZE / .95f;
        }
        else if (p->getPosY() / TILE_SIZE < -zoom_level * .95f) {
            zoom_level = -(p->getPosY()) / TILE_SIZE / .95f;
        }

        // Draw map tiles
        mapTile.use();
        mapTile.setU("zoom", 1 / zoom_level);
        mapTile.setU("camera_x", camera_x);
        mapTile.setU("aspect_ratio", aspect_ratio);
        MapDisplay* md = display.getMapDisplay();
        for (int y = 0; y < m->getMapHeight(); y++) {
            for (int x = 0; x < m->getMapHeight(); x++) {
                if (m->isObstacle(x, y)) {
                    mapTile.setU("pos", x, y);
                    mapTile.setU("color", 0.8f, 0.8f, 0.8f);
                    md->bindDrawTile();
                }
                if (m->getTile(x, y) == TileType::slope45d) {
                    mapTile.setU("pos", x, y);
                    mapTile.setU("color", 0.8f, 0.1f, 0.8f);
                    md->bindDrawDTile();
                }
                if (m->getTile(x, y) == TileType::slope45b) {
                    mapTile.setU("pos", x, y);
                    mapTile.setU("color", 0.1f, 0.8f, 0.8f);
                    md->bindDrawBTile();
                }
            }
        }

        // Draw player
        playerIcon.use();
        playerIcon.setU("aspect_ratio", aspect_ratio);
        playerIcon.setU("pos", p->getPosX() / TILE_SIZE, p->getPosY() / TILE_SIZE);
        playerIcon.setU("zoom", 1 / zoom_level);
        playerIcon.setU("camera_x", camera_x);
        //playerIcon.setU("facing_left", elements.getP1().getFacingLeft());
        PlayerDisplay* pd = display.getPd1();
        pd->bindDraw();

        // Draw ennemies A
        for (int i = 0; i < elements->getEnnemiACount(); i++) {
            goomba = elements->getEnnemiA(i);
            playerIcon.use();
            playerIcon.setU("aspect_ratio", aspect_ratio);
            playerIcon.setU("pos", goomba->getPosX() / TILE_SIZE, goomba->getPosY() / TILE_SIZE);
            playerIcon.setU("zoom", 1 / zoom_level);
            playerIcon.setU("camera_x", camera_x);
            //playerIcon.setU("facing_left", elements.getP1().getFacingLeft());
            pd->bindDraw();
        }

        // Draw ImGui elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Close application
    elements->setShouldClose();
    delete m;
    delete elements;
    t1.join();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
