#include "Light.h"
#include "ShaderHandler.h"
#include "Camera.h"
#include <glad/gl.h>


void 
Light::update(ShaderHandler& shaderHandler, Camera& camera)
{
    shaderHandler.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shaderHandler.setVec3("lightPos"  , camera.getPosition());
    shaderHandler.setVec3("lightDir"  , camera.getViewDirection());  // or equivalent
    shaderHandler.setVec3("viewPos"   , camera.getPosition());
}
