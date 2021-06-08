#ifndef INPUTS_H
#define INPUTS_H

struct GLFWwindow;
#include <queue>
#include <unordered_set>

#include <iostream>

struct i2nt {
    int first;
    int second;
};

class Inputs {
private:
    static std::queue<i2nt> _input_queue;
    static std::unordered_set<int> _pressed_keys;
    static std::string _pressed_str;

public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static size_t getInputQueueSize();
    static int getQueueFrontFirst();
    static int getQueueFrontSecond();
    static void popQueue();
    static std::unordered_set<int>& getPressedKeys();
    static void clearStr();
    static void addStr(int key);
    static std::string getPressedStr();
};

#endif
