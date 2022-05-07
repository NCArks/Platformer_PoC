#include "inputs.h"

#include <queue>
#include <string>

std::queue<i2nt> Inputs::_input_queue = std::queue<i2nt>();
std::unordered_set<int> Inputs::_pressed_keys = std::unordered_set<int>();
std::string Inputs::_pressed_str = "";

#define GLFW_REPEAT 2

void Inputs::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_REPEAT) {
        _input_queue.push(i2nt{ key, action });
    }
}

size_t Inputs::getInputQueueSize() {
    return _input_queue.size();
}

int Inputs::getQueueFrontFirst() {
    return _input_queue.front().first;
}

int Inputs::getQueueFrontSecond() {
    return _input_queue.front().second;
}

void Inputs::popQueue() {
    if (_input_queue.front().second == 1) {
        _pressed_keys.insert(_input_queue.front().first);
    } else {
        _pressed_keys.erase(_input_queue.front().first);
    }
    _input_queue.pop();
}

std::unordered_set<int>& Inputs::getPressedKeys() {
    return _pressed_keys;
}

void Inputs::clearStr() {
    _pressed_str = "";
}

void Inputs::addStr(int key) {
    _pressed_str += std::to_string(key) + " ";
}

std::string Inputs::getPressedStr() {
    return _pressed_str;
}
