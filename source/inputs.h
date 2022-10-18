#ifndef INPUTS_H
#define INPUTS_H

#include <queue>
#include <unordered_set>

#include <iostream>

struct GLFWwindow;

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
    /// <summary>
    /// Deals with any Keypresses made when the window is active. Stores it in the input queue.
    /// </summary>
    /// <param name="window">Unused</param>
    /// <param name="key">Key pressed value to be stored</param>
    /// <param name="scancode">Unused</param>
    /// <param name="action">Flag indicating if the button is pressed, or released, or repeated</param>
    /// <param name="mods">Unused</param>
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// <summary>
    /// Gets static input queue size.
    /// </summary>
    /// <returns>Size of the input queue</returns>
    static size_t getInputQueueSize();

    /// <summary>
    /// Get the First item in the input queue
    /// </summary>
    /// <returns></returns>
    static int getQueueFrontFirst();

    /// <summary>
    /// Get the Second item in the input queue.
    /// </summary>
    /// <returns></returns>
    static int getQueueFrontSecond();

    /// <summary>
    /// Removes an element for the input queue.
    /// </summary>
    static void popQueue();

    /// <summary>
    /// Gets the full set of pressed Keys.
    /// </summary>
    /// <returns>Pressed Keys unordered set</returns>
    static std::unordered_set<int>& getPressedKeys();

    /// <summary>
    /// Clears the Key pressed string made from the AddStr method.
    /// </summary>
    static void clearStr();

    /// <summary>
    /// Appends the key pressed as string to the member string, and a space.
    /// </summary>
    /// <param name="key"></param>
    static void addStr(int key);

    /// <summary>
    /// Retrieves the Key pressed in string format from the memeber string.
    /// </summary>
    /// <returns></returns>
    static std::string getPressedStr();
};

#endif
