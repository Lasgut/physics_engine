#ifndef LIGHT_H
#define LIGHT_H

#pragma once 

#include <glm/glm.hpp>
#include "ShaderHandler.h"
#include "Camera.h"

class Light
{
    public:
        Light();

        void update(ShaderHandler& shaderHandler, Camera& camera);
};

#endif