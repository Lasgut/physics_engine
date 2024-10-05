#include "ShaderHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderHandler::ShaderHandler(const char* vertexPath, const char* fragmentPath) {
    // Load and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read vertex shader
    std::ifstream vShaderFile(vertexPath);
    std::stringstream vShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    const std::string vertexCode = vShaderStream.str();
    const char* vShaderCode = vertexCode.c_str();

    // Read fragment shader
    std::ifstream fShaderFile(fragmentPath);
    std::stringstream fShaderStream;
    fShaderStream << fShaderFile.rdbuf();
    const std::string fragmentCode = fShaderStream.str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile vertex shader
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    // Compile fragment shader
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);

    // Link shaders to create a shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Clean up shaders (they're linked to the program now)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderHandler::~ShaderHandler() {
    glDeleteProgram(ID);
}

void ShaderHandler::use() {
    glUseProgram(ID);
}

void ShaderHandler::setMat4(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
