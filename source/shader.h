#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
public:
    unsigned int _id = 0;

    /// <summary>
    /// Initialize the objects with the path of the vertex and fragment shaders in glsl.
    /// </summary>
    /// <param name="vertexPath">Path of the vertex shader file</param>
    /// <param name="fragmentPath">Path of the fragment file</param>
    void initialize(const char* vertexPath, const char* fragmentPath);

    /// <summary>
    /// Use program with instance stored id
    /// </summary>
    void use();

    /// <summary>
    /// Woya I don't know open GL
    /// </summary>
    /// <param name="name"></param>
    /// <param name="b1"></param>
    void setU(const std::string &name, const bool b1) const;

    /// <summary>
    /// Woya I don't know open GL
    /// </summary>
    /// <param name="name"></param>
    /// <param name="i1"></param>
    void setU(const std::string &name, const int i1) const;

    /// <summary>
    /// Woya I don't know open GL
    /// </summary>
    /// <param name="name"></param>
    /// <param name="f1"></param>
    void setU(const std::string &name, const float f1) const;

    /// <summary>
    /// Woya I don't know open GL
    /// </summary>
    /// <param name="name"></param>
    /// <param name="f1"></param>
    /// <param name="f2"></param>
    void setU(const std::string &name, const float f1, const float f2) const;

    /// <summary>
    /// Woya I don't know open GL
    /// </summary>
    /// <param name="name"></param>
    /// <param name="f1"></param>
    /// <param name="f2"></param>
    /// <param name="f3"></param>
    void setU(const std::string &name, const float f1, const float f2, const float f3) const;
};

#endif
