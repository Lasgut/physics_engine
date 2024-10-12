#include "Light.h"
#include "ShaderHandler.h"
#include "Camera.h"
#include <glad/glad.h>

Light::Light()
{
}

void 
Light::update(ShaderHandler& shaderHandler, Camera& camera)
{
    shaderHandler.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shaderHandler.setVec3("lightPos", camera.getPosition());
}
