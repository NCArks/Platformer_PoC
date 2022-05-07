#include "shader.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>

void Shader::initialize(const char* vertexPath, const char* fragmentPath) {
    if (vertexPath == nullptr || fragmentPath == nullptr) {
        std::cout << "One of the Shader Paths are empty" << std::endl;
        return;
    }

    std::string vertexCode = std::string();
    std::string fragmentCode = std::string();
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "shader files not read" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "vertex shader not compiled\n" << infoLog << std::endl;
    };
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "fragment shader not compiled\n" << infoLog << std::endl;
    };
    _id = glCreateProgram();
    glAttachShader(_id, vertex);
    glAttachShader(_id, fragment);
    glLinkProgram(_id);
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cout << "shader program not linked\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(_id);
}

void Shader::setU(const std::string &name, const bool b1) const {
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)b1);
}
void Shader::setU(const std::string &name, const int value) const {
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}
void Shader::setU(const std::string &name, const float f1) const {
    glUniform1f(glGetUniformLocation(_id, name.c_str()), f1);
}
void Shader::setU(const std::string &name, const float f1, const float f2) const {
    glUniform2f(glGetUniformLocation(_id, name.c_str()), f1, f2);
}
void Shader::setU(const std::string &name, const float f1, const float f2, const float f3) const {
    glUniform3f(glGetUniformLocation(_id, name.c_str()), f1, f2, f3);
}
