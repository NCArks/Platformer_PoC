# Project definition
cmake_minimum_required(VERSION 3.8)
project(SomethingPlatform)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SOURCES
    "${SRC_DIR}/box_collider.cpp"
    "${SRC_DIR}/display_elements.cpp"
    "${SRC_DIR}/inputs.cpp"
    "${SRC_DIR}/logic_elements.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/map.cpp"
    "${SRC_DIR}/map_display.cpp"
    "${SRC_DIR}/movable.cpp"
    "${SRC_DIR}/player.cpp"
    "${SRC_DIR}/player_display.cpp"
    "${SRC_DIR}/shader.cpp"
)

set(IMGUI_SOURCES
    "imgui/imgui.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_impl_glfw.cpp"
    "imgui/imgui_impl_opengl3.cpp"
    "imgui/imgui_widgets.cpp"
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragment.glsl ${CMAKE_CURRENT_BINARY_DIR}/Debug/shaders/fragment.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertex.glsl ${CMAKE_CURRENT_BINARY_DIR}/Debug/shaders/ COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/tile.glsl ${CMAKE_CURRENT_BINARY_DIR}/Debug/shaders/ COPYONLY)

# imgui
target_include_directories(${PROJECT_NAME} PRIVATE "imgui")
