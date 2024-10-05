#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class ShaderHandler {
public:
    ShaderHandler(const char* vertexPath, const char* fragmentPath);
    ~ShaderHandler();

    void use();
    void setMat4(const std::string& name, const glm::mat4& value) const;

private:
    GLuint ID;
};

#endif 
