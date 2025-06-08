#ifndef FLOOR_H
#define FLOOR_H

#pragma once
#include "shapes/Rectangle.h"

class Floor
{
    public:
        Floor();
        ~Floor();

        void update(const ShaderHandler& shaderHandler);

    private:
        Rectangle shape_;
};

#endif