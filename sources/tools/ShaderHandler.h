#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderHandler
{
public:
    ShaderHandler(const char* vertexPath, const char* fragmentPath);
    
    void use(); 

    unsigned int& getID();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    unsigned int ID_;

    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif