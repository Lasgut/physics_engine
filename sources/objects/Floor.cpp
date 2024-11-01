#include "Floor.h"

Floor::Floor()
{

}

Floor::~Floor()
{

}

void 
Floor::update(const ShaderHandler &shaderHandler)
{
    auto position    = glm::vec3(0.0f, 0.0f, 0.0f);
    auto orientation = glm::vec3(0.0f, 0.0f, 0.0f);
    shape_.draw(shaderHandler, position, orientation);
}
