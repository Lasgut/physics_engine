#ifndef GUISETTINGS_H
#define GUISETTINGS_H

#pragma once
#include "Window.h"
#include "Context.h"

class GuiSettings
{
public:
    GuiSettings(const Window& window, const Context& context);
    ~GuiSettings();

    void update();

private:
    void render();
    
    bool a_{true};
    float b_{0.5};
};

#endif