#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
public:
    unsigned int _id;

    void initialize(const char* vertexPath, const char* fragmentPath);
    void use();
    void setU(const std::string &name, const bool b1) const;
    void setU(const std::string &name, const int i1) const;
    void setU(const std::string &name, const float f1) const;
    void setU(const std::string &name, const float f1, const float f2) const;
    void setU(const std::string &name, const float f1, const float f2, const float f3) const;
};

#endif
