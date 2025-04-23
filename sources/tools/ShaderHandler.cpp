#include "ShaderHandler.h"
#include "Camera.h"

ShaderHandler::ShaderHandler(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{   
    try 
    {
        ID_ = glCreateProgram();
        
        unsigned int geometryId = 0;

        auto vertexId   = createShader(vertexPath,   GL_VERTEX_SHADER);
        auto fragmentId = createShader(fragmentPath, GL_FRAGMENT_SHADER);
        if (geometryPath) 
        {
            geometryId = createShader(geometryPath, GL_GEOMETRY_SHADER);
        }
        
        glLinkProgram(ID_);
        checkCompileErrors(ID_, "PROGRAM");
        
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
        if (geometryPath) 
        {
            glDeleteShader(geometryId);
        }
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ERROR::SHADER::UNEXPECTED_EXCEPTION: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERROR::SHADER::UNKNOWN_EXCEPTION" << std::endl;
    }
}


void 
ShaderHandler::use(const Camera& camera) 
{ 
    glUseProgram(ID_); 
    setMat4("view", camera.getViewMatrix());
    setMat4("projection", camera.getProjectionMatrix());
}


void 
ShaderHandler::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(ID_, name.c_str()), 1, &value[0]); 
}


void 
ShaderHandler::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(ID_, name.c_str()), x, y); 
}


void 
ShaderHandler::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(ID_, name.c_str()), 1, &value[0]); 
}


void 
ShaderHandler::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(ID_, name.c_str()), x, y, z); 
}


void 
ShaderHandler::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(ID_, name.c_str()), 1, &value[0]); 
}


void 
ShaderHandler::setVec4(const std::string &name, float x, float y, float z, float w) const
{ 
    glUniform4f(glGetUniformLocation(ID_, name.c_str()), x, y, z, w); 
}

void 
ShaderHandler::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void 
ShaderHandler::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void 
ShaderHandler::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


unsigned int&
ShaderHandler::getID()
{
    return ID_;
}


void 
ShaderHandler::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID_, name.c_str()), (int)value); 
}


void 
ShaderHandler::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID_, name.c_str()), value); 
}


void 
ShaderHandler::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID_, name.c_str()), value); 
}


std::string 
ShaderHandler::readShaderFile(const char* path)
{
    std::ifstream     shaderFile;
    std::stringstream shaderStream;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    shaderFile.open(path);
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}


unsigned int
ShaderHandler::createShader(const char* path, GLenum shaderType)
{
    unsigned int shaderId; 

    auto code = readShaderFile(path);
    const char* shaderCode = code.c_str();
    shaderId = glCreateShader(shaderType); 
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);
    checkCompileErrors(shaderId, shaderType == GL_VERTEX_SHADER   ? "VERTEX"   :
                                 shaderType == GL_FRAGMENT_SHADER ? "FRAGMENT" :
                                 shaderType == GL_GEOMETRY_SHADER ? "GEOMETRY" : "UNKNOWN");
    glAttachShader(ID_, shaderId);

    return shaderId;
}


void 
ShaderHandler::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}