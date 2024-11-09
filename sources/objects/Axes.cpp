#include "Axes.h"

Axes::Axes()
{
}

Axes::Axes(float length)
    : length_(length)
{
}

Axes::~Axes()
{
}

void 
Axes::update(const ShaderHandler &shaderHandler)
{
    xAxis_.draw(shaderHandler,
                position_,
                xOrientation_);

    yAxis_.draw(shaderHandler,
                position_,
                yOrientation_);

    zAxis_.draw(shaderHandler,
                position_,
                zOrientation_);
}
